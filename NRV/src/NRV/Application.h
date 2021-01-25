#pragma once

#include "NRVCore.h"

#include "ThreadPool.h"

namespace NRV {

	class NRV_API Application
	{
	private:
		ThreadPool m_Processes;
		bool m_IsRunning;
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();

}