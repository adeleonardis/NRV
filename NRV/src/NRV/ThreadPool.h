#pragma once

#include "NRVCore.h"

#include <queue>
#include <functional>
#include <vector>
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
		std::thread m_TaskProcessingThread;
		std::mutex m_PoolAccess;
		std::vector<std::thread> m_Pool;
		ThreadSafeQueue<std::function<void()>> m_Tasks;
	public:
		ThreadPool();
		~ThreadPool();
		void PushTask(std::function<void()> task);
		void TaskLoop();
		void EndPool();
	};

}