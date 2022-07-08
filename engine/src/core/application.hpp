#pragma once

#include <defines.hpp> 

struct game;

// Application configuration.
struct application_config
{
    int16_t start_pos_x;
    int16_t start_pos_y;
    int16_t start_width;
    int16_t start_height;

    // The application name used in windowing, if applicable.
    char* name;
};


IRL_API bool application_create(struct game* game_inst);

IRL_API bool application_run();
