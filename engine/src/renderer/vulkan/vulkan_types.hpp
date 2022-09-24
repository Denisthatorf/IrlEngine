#pragma once
#include "defines.hpp"
#include <core/assertion.hpp>

#include <vulkan/vulkan.h>

#define VK_CHECK(expr)               \
    {                                \
        IRL_ASSERT(expr == VK_SUCCESS); \
    }

typedef struct vulkan_context 
{
#ifdef _DEBUG
    VkDebugUtilsMessengerEXT debug_messenger;
#endif

    VkInstance instance;
    VkAllocationCallbacks* allocator;
} vulkan_context;
