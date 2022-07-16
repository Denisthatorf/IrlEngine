#pragma once

#include <defines.hpp>

bool initWindow (int width, int height, const char* application_name);
void destroyWindow();

bool pollWindowEvents();