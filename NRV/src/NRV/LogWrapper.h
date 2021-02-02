#pragma once

#define IsLogging 1

#include "Log.h"

#if IsLogging
	#define LogMessage(text, log_level) Log::OutputMessage(text, log_level)
#elif
	#define LogMessage(text, log_level)
#endif