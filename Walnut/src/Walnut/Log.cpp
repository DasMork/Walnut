#include "Log.h" 

namespace Walnut {

	std::shared_ptr<spdlog::logger> Walnut::Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Walnut::Log::s_ClientLogger;

}
void Walnut::Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
	s_CoreLogger->set_level(spdlog::level::trace);

	s_ClientLogger = spdlog::stdout_color_mt("CIENT");
	s_ClientLogger->set_level(spdlog::level::trace);
}
