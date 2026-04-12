#pragma once

#include "Random/Core/Core.hpp"

#include "spdlog/spdlog.h"

namespace Rand
{
    class RAND_API Log
    {
      public:
        static void init();

        static std::shared_ptr<spdlog::logger> getCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger> getClientLogger() { return s_ClientLogger; }

      private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
} // namespace Rand

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
