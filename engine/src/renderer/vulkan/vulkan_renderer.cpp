#include "vulkan_renderer.hpp"

#include "vulkan_types.hpp"
#include "vulkan_platform.hpp"
#include "vulkan_device.hpp"

#include "core/logger.hpp"
#include <vector>
#include <string>

// static Vulkan context
static vulkan_context context;

VKAPI_ATTR VkBool32 VKAPI_CALL vk_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data);

//TODO: refactor
bool vulkan_renderer::initialize(const char* application_name, struct window* window) {
    // TODO: custom allocator.
    context.allocator = 0;

    // Setup Vulkan instance.
    VkApplicationInfo app_info = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    app_info.apiVersion = VK_API_VERSION_1_2;
    app_info.pApplicationName = application_name;
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "IrlEngine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};

    // Obtain a list of required extensions
    std::vector<const char*> required_extensions;
    window_get_required_extension_names(required_extensions);

#ifdef _DEBUG
    required_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);  // debug utilities

    CORE_LOG_DEBUG("Required extensions:");
    uint32_t length = required_extensions.size();
    for (uint32_t i = 0; i < length; ++i) {
        CORE_LOG_DEBUG(required_extensions[i]);
    }
#endif

    create_info.enabledExtensionCount = required_extensions.size();
    create_info.ppEnabledExtensionNames = required_extensions.data();

    // Validation layers.
    std::vector<const char*> required_validation_layer_names;
    uint32_t required_validation_layer_count = 0;

#ifdef _DEBUG
    CORE_LOG_DEBUG("Validation layers enabled. Enumerating...");

    // The list of validation layers required.
    required_validation_layer_names.push_back("VK_LAYER_KHRONOS_validation");
    required_validation_layer_count = required_validation_layer_names.size();

    // Obtain a list of available validation layers
    uint32_t available_layer_count = 0;
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, nullptr));
    std::vector<VkLayerProperties> available_layers(available_layer_count);
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, available_layers.data()));

    // Verify all required layers are available.
    for (uint32_t i = 0; i < required_validation_layer_count; ++i) 
	{
        CORE_LOG_DEBUG("Searching for layer: {}", required_validation_layer_names[i]);
        bool found = false;
        for (uint32_t j = 0; j < available_layers.size(); ++j) {
            if (strcmp(required_validation_layer_names[i], available_layers[j].layerName)) {
                found = true;
                CORE_LOG_DEBUG("Found.");
                break;
            }
        }

        if (!found) {
            CORE_LOG_DEBUG("Required validation layer is missing: {}", required_validation_layer_names[i]);
            return false;
        }
    }
    CORE_LOG_DEBUG("All required validation layers are present.");
#endif

    create_info.enabledLayerCount = required_validation_layer_count;
    create_info.ppEnabledLayerNames = required_validation_layer_names.data();

    VK_CHECK(vkCreateInstance(&create_info, context.allocator, &context.instance));
    CORE_LOG_DEBUG("Vulkan Instance created.");

#ifdef _DEBUG
    CORE_LOG_DEBUG("Creating Vulkan debugger...");
    uint32_t log_severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;  //|
                                                                      //    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

    VkDebugUtilsMessengerCreateInfoEXT debug_create_info = {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
    debug_create_info.messageSeverity = log_severity;
    debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
    debug_create_info.pfnUserCallback = vk_debug_callback;

    PFN_vkCreateDebugUtilsMessengerEXT func =
        (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkCreateDebugUtilsMessengerEXT");

    VK_CHECK(func(context.instance, &debug_create_info, context.allocator, &context.debug_messenger));
    CORE_LOG_DEBUG("Vulkan debugger created.");
#endif


    // Surface
    CORE_LOG_DEBUG("Creating Vulkan surface...");
    if (!window_create_vulkan_surface(window, &context)) {
        CORE_LOG_ERROR("Failed to create platform surface!");
        return false;
    }
    CORE_LOG_DEBUG("Vulkan surface created.");

    // Device creation
    if (!vulkan_device_create(&context)) {
        CORE_LOG_ERROR("Failed to create device!");
        return false;
    }



    CORE_LOG_DEBUG("Vulkan renderer initialized successfully.");
    return true;
}

void vulkan_renderer::shutdown()
{
    CORE_LOG_DEBUG("Destroying Vulkan device...");
    vulkan_device_destroy(&context);

    CORE_LOG_DEBUG("Destroying Vulkan surface...");
    if (context.surface) {
        vkDestroySurfaceKHR(context.instance, context.surface, context.allocator);
        context.surface = 0;
    }

    #ifdef _DEBUG 
    CORE_LOG_DEBUG("Destroying Vulkan debugger...");
    if (context.debug_messenger) {
        PFN_vkDestroyDebugUtilsMessengerEXT func =
            (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkDestroyDebugUtilsMessengerEXT");
        func(context.instance, context.debug_messenger, context.allocator);
    }
    #endif

    CORE_LOG_DEBUG("Destroying Vulkan instance...");
    vkDestroyInstance(context.instance, context.allocator);
}

void vulkan_renderer::resized(uint16_t width, uint16_t height) {
}

bool vulkan_renderer::begin_frame(float delta_time) {
    return true;
}

bool vulkan_renderer::end_frame(float delta_time) {
    return true;
}

VKAPI_ATTR VkBool32 VKAPI_CALL vk_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data) 
{
    switch (message_severity) {
        default:
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            CORE_LOG_ERROR(callback_data->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            CORE_LOG_WARN(callback_data->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            CORE_LOG_DEBUG(callback_data->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            CORE_LOG_TRACE(callback_data->pMessage);
            break;
    }
    return VK_FALSE;
}
