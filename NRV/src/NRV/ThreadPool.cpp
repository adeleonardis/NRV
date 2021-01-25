#include "ThreadPool.h"

namespace NRV {

	ThreadPool::ThreadPool()
		: m_IsDone(false)
	{
		m_TaskProcessingThread = std::thread(&ThreadPool::TaskLoop, this);
	}

	ThreadPool::~ThreadPool()
	{
		m_IsDone = true;
	}

	void ThreadPool::TaskLoop()
	{
		while (!m_IsDone)
		{
			std::function<void()> task;
			if (m_Tasks.TryPop(task))
			{
				PushTask(task);
			}
		}
	}

	void ThreadPool::EndPool()
	{
		m_IsDone = true;
		m_TaskProcessingThread.join();
		int size = m_Pool.size();
		for (int i = 0; i < size; i++)
			m_Pool[i].join();
	}

	void ThreadPool::PushTask(std::function<void()> task)
	{
		std::lock_guard<std::mutex> lock(m_PoolAccess);
		m_Pool.push_back(std::thread(task));
	}

}