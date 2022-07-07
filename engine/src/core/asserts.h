#pragma once

#include "defines.h"

// Disable assertions by commenting out the below line.
#define IRL_ASSERTIONS_ENABLED

#ifdef IRL_ASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

IRL_API void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

#define IRL_ASSERT(expr)                                                \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                            \
        }                                                            \
    }

#define IRL_ASSERT_MSG(expr, message)                                        \
    {                                                                     \
        if (expr) {                                                       \
        } else {                                                          \
            report_assertion_failure(#expr, message, __FILE__, __LINE__); \
            debugBreak();                                                 \
        }                                                                 \
    }

#ifdef _DEBUG
#define IRL_ASSERT_DEBUG(expr)                                          \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                            \
        }                                                            \
    }
#else
#define IRL_ASSERT_DEBUG(expr)  // Does nothing at all
#endif

#else
#define IRL_ASSERT(expr)               // Does nothing at all
#define IRL_ASSERT_MSG(expr, message)  // Does nothing at all
#define IRL_ASSERT_DEBUG(expr)         // Does nothing at all
#endif
