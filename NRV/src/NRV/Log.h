#pragma once

#include <mutex>
#include <string>

namespace NRV {

	class Log
	{
	private:
		using Lock = std::lock_guard<std::mutex>;
	public:
		enum LogLevel { Catastrophic = 0, Error, Mistake, Warning, Message };
	private:
		static std::mutex m_Mutex;
		static LogLevel m_LogLevel;
	public:
		static void OutputMessage(const std::string& text, LogLevel log_level);
		static void SetLogLevel(LogLevel log_level);
	};

}