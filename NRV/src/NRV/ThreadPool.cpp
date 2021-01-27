#include "ThreadPool.h"
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

namespace NRV {
	ThreadPool::ThreadPool()
		: m_IsDone(false), m_NewTaskThread(&ThreadPool::NewTaskLoop, this), m_EndTaskThread(&ThreadPool::EndTaskLoop, this) {}

	ThreadPool::~ThreadPool()
	{
		// Nodes should be deleted with the thread list Clear() function.
	}

	void ThreadPool::PushTask(std::function<void()> task)
	{
		m_Tasks.Append(task);
	}

	void ThreadPool::NewTaskLoop()
	{
		while (!m_IsDone)
		{
			if (!m_Tasks.IsEmpty())
			{
				std::function<void()>* current_task = new std::function<void()>(m_Tasks.Top());
				m_Tasks.Pop();

				ThreadSafe::ThreadNode* new_node = new ThreadSafe::ThreadNode();
				new_node->m_Thread = new std::thread([&](std::function<void()> *task, ThreadSafe::ThreadNode *node) {

					m_ThreadPool.Append(node);

					(*task)();
					delete task;

					while (!node);

					m_FinishedThreads.Append(node);
				}, current_task, new_node);
			}
		}

		//m_ThreadPool.Print();
	}

	void ThreadPool::EndTaskLoop()
	{
		while (!m_IsDone)
		{
			if (!m_FinishedThreads.IsEmpty())
			{
				auto ended_task = m_FinishedThreads.Pull();
				m_ThreadPool.Remove(ended_task);
			}
		}
	}

	void ThreadPool::EndPool()
	{
		m_IsDone = true;

		std::cout << "Ending the pool...\n";
		m_NewTaskThread.join();
		std::cout << "Successfully joined the new task thread\n";
		m_EndTaskThread.join();
		std::cout << "Successfully joined the end task thread\n";

		m_ThreadPool.Clear();
		std::cout << "Successfully joined cleared the thread pool\n";
	}

}