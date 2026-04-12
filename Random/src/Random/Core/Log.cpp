#include "Random/Core/Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Rand
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger   = nullptr;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger = nullptr;

    void Log::init()
    {
        spdlog::set_pattern("%^[%T:%e] %n (%l) : %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("RANDOM");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}; // namespace Rand
