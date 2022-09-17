#pragma once
#include <functional>

#include "defines.hpp"
#include "core/application.hpp"

struct game 
{
	application_config app_config;
	
    bool (*initialize) (game* game_inst);
    bool (*update) (game* game_inst, float delta_time);
    bool (*render) (game* game_inst, float delta_time);
	void (*on_resize) (game* game_inst, uint32_t width, uint32_t height);	
};

//application_config app_config;
//b8 (*initialize)(struct game* game_inst);
//b8 (*update)(struct game* game_inst, f32 delta_time);
//b8 (*render)(struct game* game_inst, f32 delta_time);
//void (*on_resize)(struct game* game_inst, u32 width, u32 height);
//void* state;
