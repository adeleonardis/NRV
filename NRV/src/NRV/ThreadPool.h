#pragma once

#include "NRVCore.h"

#include "ThreadSafe/ThreadSafeQueue.h"
#include "ThreadSafe/ThreadList.h"
#include <queue>
#include <functional>
#include <thread>
#include <mutex>

namespace NRV {

	template <typename T>
	class ThreadSafeQueue
	{
	private:
		std::mutex m_QueueAccess;
		std::queue<T> m_Queue;
	public:
		inline bool IsEmpty() const { return !m_Queue.size(); }

		void Push(T& item)
		{
			std::lock_guard<std::mutex> lock(m_QueueAccess);
			m_Queue.push(item);
		}

		bool TryPop(T& output)
		{
			if (!IsEmpty())
			{
				std::lock_guard<std::mutex> lock(m_QueueAccess);
				output = m_Queue.front();
				m_Queue.pop();
				return true;
			}
			return false;
		}
	};

	class ThreadPool
	{
	private:
		bool m_IsDone;

		std::thread m_NewTaskThread;
		std::thread m_EndTaskThread;

		ThreadSafe::Queue<std::function<void()>> m_Tasks;
		ThreadSafe::ThreadList m_ThreadPool;
		ThreadSafe::Queue<ThreadSafe::ThreadNode*> m_FinishedThreads;
	public:
		ThreadPool();
		~ThreadPool();

		void PushTask(std::function<void()> task);

		void NewTaskLoop();
		void EndTaskLoop();

		void EndPool();

	
	};

}