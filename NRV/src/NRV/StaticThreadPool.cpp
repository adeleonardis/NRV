#include "StaticThreadPool.h"

#include "LogWrapper.h"

#include <iostream>

namespace NRV {

	//
	// Public methods
	//

	StaticThreadPool::StaticThreadPool()
		: m_IsRunning(false), m_ThreadCount(0), m_ThreadArray(nullptr) {}

	StaticThreadPool::~StaticThreadPool()
	{

	}

	void StaticThreadPool::InitThreadPool(int ThreadCount)
	{
		LogMessage("Initializing static thread pool...", Log::LogLevel::Message);
		if (m_ThreadArray)
		{
			LogMessage("Thread array already initialized", Log::LogLevel::Mistake);
			return;
		}

		m_ThreadCount = ThreadCount;
		m_ThreadArray = new std::thread*[m_ThreadCount];
		for (uint32_t i = 0; i < m_ThreadCount; i++)
		{
			m_ThreadArray[i] = nullptr;
		}

		Lock lock(m_SlotQueueMutex);
		for (uint32_t i = 0; i < m_ThreadCount; i++)
		{
			m_SlotQueue.push(i);
		}
	}

	void StaticThreadPool::Run()
	{
		LogMessage("Running static thread pool...", Log::LogLevel::Message);
		if (!m_ThreadArray)
		{
			LogMessage("Trying to run uninitialized static thread pool", Log::LogLevel::Mistake);
			return;
		}

		m_IsRunning = true;
		new(&m_DoTaskLoopThread) std::thread(&StaticThreadPool::DoTask_Loop, this);
		new(&m_FinishSlotLoopThread) std::thread(&StaticThreadPool::FinishSlot_Loop, this);
	}

	void StaticThreadPool::AppendTask(std::function<void()> task)
	{
		LogMessage("Appending task to static thread pool's task queue...", Log::LogLevel::Message);
		Lock lock(m_TaskQueueMutex);
		m_TaskQueue.push(task);
	}

	void StaticThreadPool::EndPool()
	{
		LogMessage("Ending static thread pool...", Log::LogLevel::Message);
		if (!m_ThreadArray)
			return;

		if (m_IsRunning)
		{
			m_IsRunning = false;
			m_DoTaskLoopThread.join();
			m_FinishSlotLoopThread.join();
		}

		for (uint32_t i = 0; i < m_ThreadCount; i++)
		{
			if (m_ThreadArray[i])
			{
				m_ThreadArray[i]->join();
				delete m_ThreadArray[i];
				m_ThreadArray[i] = nullptr;
			}
		}
		delete m_ThreadArray;
	}

	void StaticThreadPool::TaskWrapper(std::function<void()> task, uint32_t slot)
	{
		task();
		MarkSlotAsFinished(slot);
	}

	//
	// Private methods
	//

	void StaticThreadPool::DoTask()
	{
		// Check for available array slot
		{
			bool slot_available = false;
			{
				Lock lock(m_SlotQueueMutex);
				slot_available = !m_SlotQueue.empty();
			}
			if (!slot_available)
				return;
		}

		// Check for available task
		{
			bool task_available = false;
			{
				Lock lock(m_TaskQueueMutex);
				task_available = !m_TaskQueue.empty();
			}
			if (!task_available)
				return;
		}

		LogMessage("Task and slot available in static thread pool, doing task...", Log::LogLevel::Message);

		// Get available slot
		uint32_t slot;
		{
			Lock slot_queue_lock(m_SlotQueueMutex);
			slot = m_SlotQueue.front();
			m_SlotQueue.pop();
		}

		// Get available task
		std::function<void()> task;
		{
			Lock task_queue_lock(m_TaskQueueMutex);
			task = m_TaskQueue.front();
			m_TaskQueue.pop();
		}

		m_ThreadArray[slot] = new std::thread(&StaticThreadPool::TaskWrapper, this, task, slot);
	}

	void StaticThreadPool::DoTask_Loop()
	{
		while (m_IsRunning)
			DoTask();
	}

	void StaticThreadPool::MarkSlotAsFinished(uint32_t slot)
	{
		LogMessage("Marking slot as finished in static thread pool...", Log::LogLevel::Message);
		Lock lock(m_FinishedSlotQueueMutex);
		m_FinishedSlotQueue.push(slot);
	}

	void StaticThreadPool::FinishSlot()
	{
		// Get finished slot it available
		uint32_t slot;
		{
			Lock lock(m_FinishedSlotQueueMutex);
			if (!m_FinishedSlotQueue.empty())
			{
				slot = m_FinishedSlotQueue.front();
				m_FinishedSlotQueue.pop();
			}
			else
				return;
		}

		LogMessage("Slot available to finish in static thread pool, finishing slot...", Log::LogLevel::Message);

		m_ThreadArray[slot]->join();
		delete m_ThreadArray[slot];
		m_ThreadArray[slot] = nullptr;

		Lock lock(m_SlotQueueMutex);
		m_SlotQueue.push(slot);
	}

	void StaticThreadPool::FinishSlot_Loop()
	{
		while (m_IsRunning)
			FinishSlot();
	}

}