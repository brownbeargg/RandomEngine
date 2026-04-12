#pragma once

#if defined(RAND_PLATFORM_WINDOWS)
    #if defined(RAND_BUILD_DLL)
        #define RAND_API __declspec(dllexport)
    #else
        #define RAND_API __declspec(dllimport)
    #endif
#else
    #error Random doesn't support this platform
#endif

#define RAND_ENABLE_ASSERTS

#include "Random/Core/Log.hpp"

#if defined(RAND_ENABLE_ASSERTS)
    #define RAND_CORE_ASSERT(x, ...)                                                                                   \
        if (x)                                                                                                         \
            ;                                                                                                          \
        else                                                                                                           \
        {                                                                                                              \
            RAND_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__);                                                      \
            __debugbreak();                                                                                            \
        }

    #define RAND_CORE_VERIFY(x, ...)                                                                                   \
        if (x)                                                                                                         \
            ;                                                                                                          \
        else                                                                                                           \
        {                                                                                                              \
            RAND_CORE_ERROR("Verification Failed {0}", __VA_ARGS__);                                                   \
        }

    #define RAND_ASSERT(x, ...)                                                                                        \
        if (x)                                                                                                         \
            ;                                                                                                          \
        else                                                                                                           \
        {                                                                                                              \
            RAND_ERROR("Assertion Failed {0}", __VA_ARGS__)                                                            \
        }

    #define RAND_VERIFY(x, ...)                                                                                        \
        if (x)                                                                                                         \
            ;                                                                                                          \
        else                                                                                                           \
        {                                                                                                              \
            RAND_ERROR("Verification Failed {0}", __VA_ARGS__);                                                        \
        }
#else
    #define RAND_CORE_ASSERT(x, ...)
    #define RAND_CORE_VERIFY(x, ...) x;

    #define RAND_ASSERT(x, ...)
    #define RAND_VERIFY(x, ...) x;
#endif

#define BIT(x) (1 << x)
