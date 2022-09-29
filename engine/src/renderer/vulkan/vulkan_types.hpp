#pragma once
#include "defines.hpp"
#include <core/assertion.hpp>

#include <vulkan/vulkan.h>

#define VK_CHECK(expr)               \
    {                                \
        IRL_ASSERT(expr == VK_SUCCESS); \
    }

struct vulkan_swapchain_support_info {
    VkSurfaceCapabilitiesKHR capabilities;
    uint32_t format_count;
    VkSurfaceFormatKHR* formats;
    uint32_t present_mode_count;
    VkPresentModeKHR* present_modes;
};

struct vulkan_device {
    VkPhysicalDevice physical_device;
    VkDevice logical_device;
    vulkan_swapchain_support_info swapchain_support;
    int32_t graphics_queue_index;
    int32_t present_queue_index;
    int32_t transfer_queue_index;

    VkQueue graphics_queue;
    VkQueue present_queue;
    VkQueue transfer_queue;

    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    VkPhysicalDeviceMemoryProperties memory;
};

typedef struct vulkan_context 
{
#ifdef _DEBUG
    VkDebugUtilsMessengerEXT debug_messenger;
#endif

    VkInstance instance;
    VkAllocationCallbacks* allocator;
    VkSurfaceKHR surface;
    vulkan_device device;
} vulkan_context;
