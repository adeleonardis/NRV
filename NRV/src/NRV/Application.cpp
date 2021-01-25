#include "Application.h"

#include <iostream>
#include <thread>

static void tempfunction(const bool* IsRunning) { while (*IsRunning) std::cout << std::this_thread::get_id() << '\n'; }

namespace NRV {
	Application::Application()
		: m_IsRunning(true) {}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		// Push tasks, i.e. threads for while loops
		m_Processes.PushTask([=]() { tempfunction(&m_IsRunning); });
		m_Processes.PushTask([=]() { tempfunction(&m_IsRunning); });
		m_Processes.PushTask([=]() { tempfunction(&m_IsRunning); });

		//while (true);
		std::cin.get();
		m_IsRunning = false;

		// Pop/end tasks
		m_Processes.EndPool();
	}

}