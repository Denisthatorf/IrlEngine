#include "platform.hpp"

// Windows platform layer.
#if PLATFORM_WINDOWS

#include <windows.h>
//#include <windowsx.h>  // param input extraction
#include <stdlib.h>

// Clock
static double clock_frequency;
static LARGE_INTEGER start_time;

double platform_get_absolute_time() {
    LARGE_INTEGER now_time;
    QueryPerformanceCounter(&now_time);
    return (double)now_time.QuadPart * clock_frequency;
}

void platform_sleep(uint64_t ms) {
    Sleep(ms);
}

#endif // KPLATFORM_WINDOWS
