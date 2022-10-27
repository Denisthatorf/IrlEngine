#pragma once

#include <defines.hpp>
#include <game_types.hpp>

struct MyGame : public Game
{
    MyGame( int16_t start_pos_x,
            int16_t start_pos_y,
            int16_t start_width,
            int16_t start_height,
            char* name);
    ~MyGame();

    bool Initialize() override;
    bool Update(float delta_time) override; 
    bool Render(float delta_time) override;
    void OnResize(uint32_t width, uint32_t height) override; 

    float delta_time;
};
