#pragma once

#include "RandomPch.hpp"

namespace Rand
{
    namespace Profiler
    {
        struct Result
        {
            std::string Name;
            long long Start, End;
            uint32_t ThreadID;
        };

        class Timer
        {
          public:
            Timer(const char* name) : m_Name(name), m_StartPoint(std::chrono::high_resolution_clock::now()) {}
            virtual ~Timer() = default;

            void start() { m_StartPoint = std::chrono::high_resolution_clock::now(); }
            Result stop()
            {
                auto endPoint = std::chrono::high_resolution_clock::now();

                long long startTime = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint)
                                          .time_since_epoch()
                                          .count();
                long long endTime = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint)
                                        .time_since_epoch()
                                        .count();

                start();
                return {.Name = m_Name,
                    .Start = startTime,
                    .End = endTime,
                    .ThreadID = std::this_thread::get_id()._Get_underlying_id()};
            }

          private:
            const char* m_Name;
            std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
        };
    } // namespace Profiler
} // namespace Rand
