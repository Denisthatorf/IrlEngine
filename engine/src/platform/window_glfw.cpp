#include "window.hpp"

#ifdef USE_GLFW

#include <GL/glew.h>
#include <renderer/opengl/opengl_platform.hpp>

#include <renderer/vulkan/vulkan_types.hpp>
#include <renderer/vulkan/vulkan_platform.hpp>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <core/logger.hpp>


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

    if(!glfwInit())
        return false;

    //TODO: check why is it an error
    //glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // uncomment these lines if on Apple OS X
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/


    //TODO: make it on opengl only
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //TODO: make it on mac only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    state->glfw_window = glfwCreateWindow(width, height, application_name, NULL, NULL);

	//TODO: set window callback
    if(!state->glfw_window)
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

bool window_create_vulkan_surface(window *window, vulkan_context *context)
{
    internal_state *state = (internal_state *)window->internal_state;
    VkResult err = glfwCreateWindowSurface(context->instance, state->glfw_window, NULL, &context->surface);
    if (err != VK_SUCCESS)
    {
        CORE_LOG_CRITICAL("Can't create vulkan window surfase");
        return false;
    }

    return true;
}

#endif

void window_set_opengl_context(window* window)
{
    internal_state *state = (internal_state *)window->internal_state;
    glfwMakeContextCurrent(state->glfw_window);
}