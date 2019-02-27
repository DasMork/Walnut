#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Walnut
{

	class WALNUT_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define WN_CORE_FATAL(...) ::Walnut::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define WN_CORE_ERROR(...) ::Walnut::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WN_CORE_WARNING(...) ::Walnut::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WN_CORE_LOG(...) ::Walnut::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define WN_FATAL(...) ::Walnut::Log::GetClientLogger()->critical(__VA_ARGS__)
#define WN_ERROR(...) ::Walnut::Log::GetClientLogger()->error(__VA_ARGS__)
#define WN_WARNING(...) ::Walnut::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WN_LOG(...) ::Walnut::Log::GetClientLogger()->trace(__VA_ARGS__)
