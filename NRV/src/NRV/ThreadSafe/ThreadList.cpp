#include "ThreadList.h"

#pragma once

#include <mutex>
#include <iostream>

namespace NRV {
	namespace ThreadSafe {

		ThreadList::ThreadList()
			: head(nullptr), tail(nullptr) {}

		void ThreadList::Append(ThreadNode* node)
		{
			std::lock_guard<std::mutex> lock(m_Mutex);

			node->previous = tail;
			if (!head)
			{
				head = node;
				tail = node;
			}
		}

		void ThreadList::Remove(ThreadNode* node)
		{
			if (!node)
				return;

			std::lock_guard<std::mutex> lock(m_Mutex);

			if (node->next)
				node->next->previous = node->previous;
			else
				tail = node->previous;

			if (node->previous)
				node->previous->next = node->next;
			else
				head = node->next;

			node->m_Thread->join();
			delete node->m_Thread;
			delete node;
		}

		ThreadList::~ThreadList()
		{
			Clear();
		}

		void ThreadList::Clear()
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			ThreadNode* nextnode;
			while (head)
			{
				nextnode = head->next;

				head->m_Thread->join();
				delete head->m_Thread;
				delete head;

				head = nextnode;
			}

			head = nullptr;
			tail = nullptr;
		}

		void ThreadList::Print()
		{
			std::lock_guard<std::mutex> lock(m_Mutex);

			ThreadNode* node = head;
			while (node)
			{
				std::cout << node->m_Thread->get_id() << '\n';
				node = node->next;
			}
		}

	}
}

std::ostream& operator<<(std::ostream& os, std::thread* t) 
{
	os << t->get_id();
	return os;
}