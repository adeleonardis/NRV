#pragma once

#ifdef NRV_PLATFORM_WINDOWS

extern NRV::Application* NRV::CreateApplication();

int main(int argc, char** argv)
{
	auto app = NRV::CreateApplication();
	app->Run();
	delete app;
}

#endif