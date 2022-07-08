#include "window.hpp"

#if PLATFORM_LINUX

//#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

static GLFWwindow* window;

bool initWindow(int width, int height, const char* application_name)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, application_name, NULL, NULL);

	return window != nullptr;
}

bool pollWindowEvents()
{
    if(!glfwWindowShouldClose(window))
    {         
        glfwPollEvents();
        return true;
    }
    return false;    
}

void destroyWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
#endif
