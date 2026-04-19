#pragma once

#include "Random/Core/Core.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace Rand
{
    class Log final
    {
      public:
        static std::shared_ptr<spdlog::logger> getCoreLogger() { return get().m_CoreLogger; }
        static std::shared_ptr<spdlog::logger> getClientLogger() { return get().m_ClientLogger; }

        /**
         * @brief Initializes the client logger and core logger
         */
        static void init()
        {
            spdlog::set_pattern("%^[%T:%e] %n (%l) : %v%$");

            get().m_CoreLogger = spdlog::stdout_color_mt("RANDOM");
            get().m_CoreLogger->set_level(spdlog::level::trace);

            get().m_ClientLogger = spdlog::stdout_color_mt("APP");
            get().m_ClientLogger->set_level(spdlog::level::trace);
        }

      private:
        static Log& get() { return s_Instance; }

      private:
        static Log s_Instance;

        std::shared_ptr<spdlog::logger> m_CoreLogger;
        std::shared_ptr<spdlog::logger> m_ClientLogger;
    };

    // clang-format off
    #define RAND_CORE_TRACE(...) Rand::Log::getCoreLogger()->trace(__VA_ARGS__)
    #define RAND_CORE_INFO(...)  Rand::Log::getCoreLogger()->info(__VA_ARGS__)
    #define RAND_CORE_WARN(...)  Rand::Log::getCoreLogger()->warn(__VA_ARGS__)
    #define RAND_CORE_ERROR(...) Rand::Log::getCoreLogger()->error(__VA_ARGS__)
    #define RAND_CORE_FATAL(...) Rand::Log::getCoreLogger()->fatal(__VA_ARGS__)
    
    #define RAND_TRACE(...) Rand::Log::getClientLogger()->trace(__VA_ARGS__)
    #define RAND_INFO(...)  Rand::Log::getClientLogger()->info(__VA_ARGS__)
    #define RAND_WARN(...)  Rand::Log::getClientLogger()->warn(__VA_ARGS__)
    #define RAND_ERROR(...) Rand::Log::getClientLogger()->error(__VA_ARGS__)
    #define RAND_FATAL(...) Rand::Log::getClientLogger()->fatal(__VA_ARGS__)
    // clang-format on
} // namespace Rand
