#pragma once

#include <defines.hpp>
#include <game_types.hpp>

struct game_state
{
    float delta_time;
};

bool game_initialize(game* game_inst);

bool game_update(game* game_inst, float delta_time);

bool game_render(game* game_inst, float delta_time);

void game_on_resize(game* game_inst, uint32_t width, uint32_t height);
