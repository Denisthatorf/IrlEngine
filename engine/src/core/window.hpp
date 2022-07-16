#pragma once

#include <defines.hpp>

bool initWindow (int width, int height, const char* application_name);
void destroyWindow();

bool pollWindowEvents();

#pragma region Window Callbacks

typedef void (*mouseMoved_t)(double x, double y);
typedef void (*mouseScroll_t)(double x, double y);
typedef void (*mouseButton_t)(int button);
typedef void (*mouseKey_t)(int key, int scancode);
typedef void (*windowResize_t)(int width, int height);
typedef void (*windowClosed_t)();

void addMouseMovedCallback(void (*function)(double x, double y));
void addMouseScrollCallback(mouseScroll_t function);

void addMouseButtonPressedCallback(mouseButton_t function);
void addMouseButtonReleasedCallback(mouseButton_t function);

void addKeyPressedCallback(mouseKey_t function);
void addKeyReleasedCallback(mouseKey_t function);

void addWindowResizeCallback(windowResize_t function);
void addWindowCloseCallback(windowClosed_t function);

#pragma endregion

