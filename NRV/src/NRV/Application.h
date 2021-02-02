#pragma once

#include "NRVCore.h"

#include "StaticThreadPool.h"

#include "Graphics/RenderingHardwareInterface.h";

namespace NRV {

	class NRV_API Application
	{
	private:
		StaticThreadPool m_Processes;
		Graphics::RenderingHardwareInterface* m_RHI;
		bool m_IsRunning;
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();

}