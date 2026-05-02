#pragma once

#include "Random/Core/Log.hpp"

#include <cstdlib>

#if defined(_MSVC_VER)
    #define RAND_DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
    #define RAND_DEBUG_BREAK() __builtin_trap()
#else
    #define RAND_DEBUG_BREAK std::abort()
#endif

#if defined(RAND_ENABLE_DEBUG_ASSERTS)
    #define RAND_CORE_ASSERT(x, ...)                                                                                   \
        do                                                                                                             \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                RAND_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__);                                                  \
                RAND_DEBUG_BREAK();                                                                                    \
            }                                                                                                          \
        } while (0)

    #define RAND_CORE_VERIFY(x, ...)                                                                                   \
        do                                                                                                             \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                RAND_CORE_ERROR("Verification Failed {0}", __VA_ARGS__);                                               \
                RAND_DEBUG_BREAK();                                                                                    \
            }                                                                                                          \
        } while (0)

    #define RAND_ASSERT(x, ...)                                                                                        \
        do                                                                                                             \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                RAND_ERROR("Assertion Failed {0}", __VA_ARGS__);                                                       \
                RAND_DEBUG_BREAK();                                                                                    \
            }                                                                                                          \
        } while (0)

    #define RAND_VERIFY(x, ...)                                                                                        \
        do                                                                                                             \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                RAND_ERROR("Verification Failed {0}", __VA_ARGS__);                                                    \
                RAND_DEBUG_BREAK();                                                                                    \
            }                                                                                                          \
            \                                                                                                          \
        } while (0)
#else
    #define RAND_CORE_ASSERT(x, ...)
    #define RAND_CORE_VERIFY(x, ...) x

    #define RAND_ASSERT(x, ...)
    #define RAND_VERIFY(x, ...) x
#endif

#define RAND_CORE_RELEASE_ASSERT(x, ...)                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            RAND_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__);                                                      \
            RAND_DEBUG_BREAK();                                                                                        \
            std::abort();                                                                                              \
        }                                                                                                              \
    } while (0)

#define RAND_RELEASE_ASSERT(x, ...)                                                                                    \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            RAND_ERROR("Assertion Failed {0}", __VA_ARGS__);                                                           \
            RAND_DEBUG_BREAK();                                                                                        \
            std::abort();                                                                                              \
        }                                                                                                              \
    } while (0)
