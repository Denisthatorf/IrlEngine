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