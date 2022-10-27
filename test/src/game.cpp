#include "game.hpp"

#include <defines.hpp>
//#include <core/logger.hpp>

MyGame::MyGame ( int16_t start_pos_x,
        int16_t start_pos_y,
        int16_t start_width,
        int16_t start_height,
        char* name )	
{
	app_config.start_pos_x = 100;
    app_config.start_pos_y = 100;
    app_config.start_width = 1280;
    app_config.start_height = 720;
    app_config.name = "IrlEngine";

}

MyGame::~MyGame() {}

bool MyGame::Initialize()
{
	return true;
	//CLIENT_LOG_DEBUG("game_initialize() called!");
}

bool MyGame::Update(float delta_time)
{
	return true;
}

bool MyGame::Render(float delta_time)
{
	return true;
}


void MyGame::OnResize(uint32_t width, uint32_t height)
{
	
}


