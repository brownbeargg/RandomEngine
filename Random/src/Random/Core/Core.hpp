#pragma once

#if defined(RAND_PLATFORM_WINDOWS)
#else
    #error Random does NOT support this platform
#endif

#define BIT(x) (1 << x)
