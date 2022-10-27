#pragma once
#include <functional>

#include "defines.hpp"
#include "core/application.hpp"

struct Game 
{
    virtual ~Game() {};

    virtual bool Initialize () = 0;
    virtual bool Update (float delta_time) = 0;
    virtual bool Render (float delta_time) = 0;
	virtual void OnResize (uint32_t width, uint32_t height) = 0;

	application_config app_config;
};