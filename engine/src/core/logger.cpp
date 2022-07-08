#include "logger.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

static bool isInitialized = false; 

static std::shared_ptr<spdlog::logger> coreLogger;
static std::shared_ptr<spdlog::logger> clientLogger;

std::shared_ptr<spdlog::logger> getCoreLogger() { return coreLogger; }
std::shared_ptr<spdlog::logger> getClientLogger() { return clientLogger; }

void initLogger() 
{
	if(isInitialized)
	{
		CORE_LOG_WARN("Logger is allready initialized"); return;
	}

	spdlog::set_pattern("%^[%T] %n: %v%$");
	coreLogger = spdlog::stdout_color_mt("IrlEngine");
	coreLogger->set_level(spdlog::level::trace);
	clientLogger = spdlog::stdout_color_mt("Application");
	clientLogger->set_level(spdlog::level::trace);
}

