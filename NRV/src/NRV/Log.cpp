#include "Log.h"

#include <iostream>

namespace NRV {

	Log::LogLevel Log::m_LogLevel = Log::LogLevel::Message;
	std::mutex Log::m_Mutex;

	void Log::OutputMessage(const std::string& text, LogLevel log_level)
	{
		if (m_LogLevel < log_level)
			return;
		Lock lock(m_Mutex);
		std::cout << "[Log " << log_level << "]: " << text << '\n';
	}

	void Log::SetLogLevel(LogLevel log_level)
	{
		m_LogLevel = log_level;
	}

}