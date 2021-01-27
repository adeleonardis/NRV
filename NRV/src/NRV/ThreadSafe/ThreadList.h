#pragma once

#include <mutex>
#include <iostream>
#include <functional>

namespace NRV {
	namespace ThreadSafe {

		class ThreadNode
		{
		public:
			std::thread *m_Thread;
			ThreadNode *previous, *next;
		public:
			ThreadNode()
				: m_Thread(nullptr), previous(nullptr), next(nullptr) {}
		};

		// Tmeplate specialization for thread??

		class ThreadList
		{
		private:
			ThreadNode* head, * tail;
			std::mutex m_Mutex;
		public:
			ThreadList();
			~ThreadList();
			void Append(ThreadNode* node);
			void Remove(ThreadNode* node);
			inline std::mutex& GetMutex() { return m_Mutex; }
			ThreadNode* GetHead() { return head; }
			void Clear();
			void Print();
		};
	}
}