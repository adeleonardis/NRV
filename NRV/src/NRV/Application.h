#pragma once

#include "NRVCore.h"

namespace NRV {

	class NRV_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();

}