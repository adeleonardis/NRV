#pragma once

#ifdef NRV_PLATFORM_WINDOWS
	#ifdef NRV_EXPORT_DLL
		#define NRV_API __declspec(dllexport)
	#else
		#define NRV_API __declspec(dllimport)
	#endif
#else
	#error Platform not supported!
#endif