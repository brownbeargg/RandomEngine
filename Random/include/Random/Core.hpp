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

#define BIT(x) (1 << x)
