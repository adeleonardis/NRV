#include "Application.h"

#include <iostream>
#include <thread>

#include "LogWrapper.h"

#include "Graphics/OpenGL/OpenGL_RHI.h";

static void tempfunction(const bool* IsRunning) {
	std::cout << "Thread ID: " << std::this_thread::get_id() << '\n';
	while (*IsRunning);
}

namespace NRV {
	Application::Application()
		: m_RHI(nullptr), m_IsRunning(true)
	{
		m_Processes.InitThreadPool(3);
		m_RHI = new Graphics::OpenGL();
	}

	Application::~Application()
	{
		delete m_RHI;
	}

	void Application::Run()
	{
		m_Processes.Run();
		// Push tasks, i.e. threads for while loops
		m_Processes.AppendTask([&]() { tempfunction(&m_IsRunning); });
		m_Processes.AppendTask([&]() { tempfunction(&m_IsRunning); });
		m_Processes.AppendTask([&]() { tempfunction(&m_IsRunning); });

		//while (true);
		std::cin.get();
		m_IsRunning = false;

		// Pop/end tasks
		m_Processes.EndPool();
	}

}