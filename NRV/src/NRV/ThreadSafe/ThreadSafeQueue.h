#pragma once

#include <mutex>
#include <queue>
#include <iostream>

namespace NRV {
	namespace ThreadSafe {

		template <typename T>
		class Queue
		{
		private:
			std::mutex m_Mutex;
			std::queue<T> m_Queue;
		public:
			void Append(T& item)
			{
				std::lock_guard<std::mutex> lock(m_Mutex);

				m_Queue.push(item); 
			}

			void Pop()
			{
				std::lock_guard<std::mutex> lock(m_Mutex);

				m_Queue.pop();
			}

			T& Top()
			{
				std::lock_guard<std::mutex> lock(m_Mutex);

				return m_Queue.front();
			}

			T& Pull()
			{
				std::lock_guard<std::mutex> lock(m_Mutex);

				T& output = m_Queue.front();
				m_Queue.pop();
				return output;
			}

			bool TryPop(T& output)
			{
				std::lock_guard<std::mutex> lock(m_Mutex);
				if (!m_Queue.empty())
				{
					output = m_Queue.front();
					m_Queue.pop();
					return true;
				}
				return false;
			}

			bool IsEmpty()
			{
				std::lock_guard<std::mutex> lock(m_Mutex);
				return m_Queue.empty();
			}
		};

	}
}