#include "nebula/core/Log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>


namespace nebula
{
std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

void Log::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    s_CoreLogger = spdlog::stdout_color_mt("NEBULA");

    s_CoreLogger->set_level(spdlog::level::trace);

    NEBULA_INFO("Logger initialized");
}
} // namespace nebula