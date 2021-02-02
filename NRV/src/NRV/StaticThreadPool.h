#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <functional>


namespace NRV {

	class StaticThreadPool
	{
	private:
		using Lock = std::lock_guard<std::mutex>;
	private:
		bool m_IsRunning;

		int m_ThreadCount;
		std::thread** m_ThreadArray;

		std::mutex m_SlotQueueMutex;
		std::queue<uint32_t> m_SlotQueue;

		std::mutex m_TaskQueueMutex;
		std::queue<std::function<void()>> m_TaskQueue;
		std::thread m_DoTaskLoopThread;

		std::mutex m_FinishedSlotQueueMutex;
		std::queue<uint32_t> m_FinishedSlotQueue;
		std::thread m_FinishSlotLoopThread;
	public:
		StaticThreadPool();
		~StaticThreadPool();
		void InitThreadPool(int ThreadCount);
		void Run();
		void AppendTask(std::function<void()> task);
		void EndPool();
	private:
		void DoTask();
		void DoTask_Loop();
		void TaskWrapper(std::function<void()> task, uint32_t queue_slot);
		void MarkSlotAsFinished(uint32_t slot);
		void FinishSlot();
		void FinishSlot_Loop();
	};

}
