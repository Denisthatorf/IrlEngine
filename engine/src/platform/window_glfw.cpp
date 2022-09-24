#include "window.hpp"
#include <cstdint>

#ifdef USE_GLFW

#include <cstdlib>
#include <renderer/vulkan/vulkan_platform.hpp>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

struct internal_state {
	GLFWwindow* glfw_window;
};

bool window_create(
    window* window,
    const char* application_name,
    int32_t x,
    int32_t y,
    int32_t width,
    int32_t height
    )
 {
    window->internal_state = malloc(sizeof(internal_state));
    internal_state* state = (internal_state*)window->internal_state;

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    state->glfw_window = glfwCreateWindow(width, height, application_name, NULL, nullptr);

	//TODO: set window callback
    if(state->glfw_window == nullptr)
        return false;

	return true;
}

bool window_pollWindowEvents(window* window) {
    internal_state* state = (internal_state*)window->internal_state;

    if(!glfwWindowShouldClose(state->glfw_window))
    {         
        glfwPollEvents();
        return true;
    }
    return false;    
}

void window_destroy(window* window) {
    internal_state* state = (internal_state*)window->internal_state;

    glfwDestroyWindow(state->glfw_window);
    glfwTerminate();
}

void window_get_required_extension_names(std::vector<const char*>& names) {
    uint32_t count;
    const char** extensions = glfwGetRequiredInstanceExtensions(&count);    
    
    for (uint32_t i = 0; i < count; i++) {
        names.push_back( extensions[i] );
    }
}

#endif