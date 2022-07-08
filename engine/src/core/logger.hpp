#pragma once
#include <defines.hpp>

#include <memory>
#include <spdlog/spdlog.h>

void initLogger();

IRL_API std::shared_ptr<spdlog::logger> getCoreLogger();
IRL_API std::shared_ptr<spdlog::logger> getClientLogger();

// Core log macros
#define CORE_LOG_TRACE(...)		getCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOG_DEBUG(...)		getCoreLogger()->debug(__VA_ARGS__)
#define CORE_LOG_WARN(...)		getCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...)		getCoreLogger()->error(__VA_ARGS__)
#define CORE_LOG_CRITICAL(...)  getCoreLogger()->critical(__VA_ARGS__)
// Client log macros
#define CLIENT_LOG_TRACE(...)	      getClientLogger()->trace(__VA_ARGS__)
#define CLIENT_LOG_DEBUG(...)	      getClientLogger()->debug(__VA_ARGS__)
#define CLIENT_LOG_WARN(...)	      getClientLogger()->warn(__VA_ARGS__)
#define CLIENT_LOG_ERROR(...)	      getClientLogger()->error(__VA_ARGS__)
#define CLIENT_LOG_CRITICAL(...)	  getClientLogger()->critical(__VA_ARGS__)

