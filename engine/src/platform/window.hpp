#pragma once
#include <defines.hpp>

//TODO: use platform dependent windows
//TODO: think about using abstract window class if needed

struct window
{
    void* internal_state;
};

bool window_create(
    window* window_state,
    const char* application_name,
    int32_t x,
    int32_t y,
    int32_t width,
    int32_t height
	);

void window_destroy(window* window);
bool window_pollWindowEvents(window* window); 
