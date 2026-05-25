#pragma once

#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

#include <memory>

namespace nebula
{
class Log
{
  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

  private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
};
} // namespace nebula

#define NEBULA_TRACE(...) ::nebula::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NEBULA_INFO(...) ::nebula::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NEBULA_WARN(...) ::nebula::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NEBULA_ERROR(...) ::nebula::Log::GetCoreLogger()->error(__VA_ARGS__)