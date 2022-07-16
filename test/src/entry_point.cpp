#include "game.hpp"
#include <entry_point.hpp>

// Define the function to create a game
bool create_game(game* out_game) {
    // Application configuration.
    out_game->app_config.start_pos_x = 100;
    out_game->app_config.start_pos_y = 100;
    out_game->app_config.start_width = 1280;
    out_game->app_config.start_height = 720;
    out_game->app_config.name = "IrlEngine";
    out_game->update = game_update;
    out_game->render = game_render;
    out_game->initialize = game_initialize;
    out_game->on_resize = game_on_resize;

     std::function<bool(game* game_inst)> initialize =  game_initialize;
    auto res = initialize(out_game);
    // Create the game state.
    //out_game->state = platform_allocate(sizeof(game_state), FALSE);

    return true;
} 
