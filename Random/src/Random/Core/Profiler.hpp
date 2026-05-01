#pragma once

#include "RandomPch.hpp"

namespace Rand
{
    namespace Profiler
    {
        struct Result
        {
            const char* Time;
            float Value;
        };

        class Timer final
        {
          public:
            Timer(const char* name) : m_Name(name), m_StartPoint(std::chrono::high_resolution_clock::now()) {}
            ~Timer() = default;

            void start() { m_StartPoint = std::chrono::high_resolution_clock::now(); }
            Result stop()
            {
                auto endPoint = std::chrono::high_resolution_clock::now();

                long long startTime =
                    std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
                long long endTime =
                    std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

                start();
                return {.Time = m_Name, .Value = (endTime - startTime) * 0.001f};
            }

          private:
            const char* m_Name;
            std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
        };
    } // namespace Profiler
} // namespace Rand
