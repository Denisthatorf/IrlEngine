#pragma once
#include "defines.hpp"

IRL_API void report_assertion_failure(const char* expression, const char* message, const char* file, int32_t line);

#define IRL_ASSERT(expr)                                             \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
        }                                                            \
    }

#define IRL_ASSERT_MSG(expr, message)                                     \
    {                                                                     \
        if (expr) {                                                       \
        } else {                                                          \
            report_assertion_failure(#expr, "", __FILE__, __LINE__);      \
        }                                                                 \
    }

#ifdef NDEBUG
#define IRL_ASSERT_DEBUG(expr, message)                                           \
    {                                                                             \
        if (expr) {                                                               \
        } else {                                                                  \
            report_assertion_failure(#expr, "", __FILE__, __LINE__);              \
        }                                                                         \
    }
#else
#define IRL_ASSERT_DEBUG(expr) 
#endif
