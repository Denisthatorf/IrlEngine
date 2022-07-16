#include "window.hpp"

#if PLATFORM_LINUX

//#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <utils/event.hpp>

static GLFWwindow* window;

static void setWindowCallbacks();

bool initWindow(int width, int height, const char* application_name) {
    bool isInited = true;

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, application_name, NULL, NULL);

    if(window != nullptr)
    {
        setWindowCallbacks();
    }
    else
    {
        isInited = false;
    }

	return isInited;
}

bool pollWindowEvents() {
    if(!glfwWindowShouldClose(window))
    {         
        glfwPollEvents();
        return true;
    }
    return false;    
}

void destroyWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

#pragma region Window Callbacks

irl::f_event<void(double x, double y)> mouseMoved;
irl::f_event<void(double x, double y)> mouseScroll;

irl::f_event<void(int button)> mouseButtonPressed;
irl::f_event<void(int button)> mouseButtonReleased;

irl::f_event<void(int key, int scancode)> keyPressed;
irl::f_event<void(int key, int scancode)> keyReleased;

irl::f_event<void(int width, int height)> windowResized;
irl::f_event<void()> windowClosed;

//----------

void addMouseMovedCallback(mouseMoved_t function) { mouseMoved += function; }
void addMouseScrollCallback(mouseScroll_t function) { mouseScroll += function; }

void addMouseButtonPressedCallback(mouseButton_t function) { mouseButtonPressed += function; }
void addMouseButtonReleasedCallback(mouseButton_t function) { mouseButtonReleased += function; }

void addKeyPressedCallback(mouseKey_t function) { keyPressed += function; }
void addKeyReleasedCallback(mouseKey_t function) { keyReleased += function; }

void addWindowResizeCallback(windowResize_t function) { windowResized += function; }
void addWindowCloseCallback(windowClosed_t function) { windowClosed += function; }

//------------

static void mouseMovedCallback(GLFWwindow* window, double x, double y) { mouseMoved.invoke(x, y); }
static void mouseScrollCallback(GLFWwindow* window, double x, double y) { mouseScroll.invoke(x, y); }

static void windowResizeCallback(GLFWwindow* window, int width, int height) { windowResized.invoke(width, height); }
static void windowCloseCallback(GLFWwindow* window) { windowClosed.invoke(); }

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        mouseButtonPressed.invoke(button);
	else
        mouseButtonReleased.invoke(button);

}

static void keyCallback(GLFWwindow*, int key, int scancode, int action, int mods) 
{
    if(action == GLFW_PRESS)
        keyPressed.invoke(key, scancode);
    else 
        keyReleased.invoke(key, scancode);
}


static void setWindowCallbacks()
{
	glfwSetCursorPosCallback(window, mouseMovedCallback);
	glfwSetScrollCallback(window, mouseScrollCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetWindowCloseCallback(window, windowCloseCallback);
}

#pragma endregion

#endif
