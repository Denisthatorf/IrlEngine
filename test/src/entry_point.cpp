#include "game.hpp"
#include <entry_point.hpp>

// Define the function to create a game
Game* create_game() {
    MyGame* game = new MyGame(
        100, 100,
        1280, 720,
        "IrlEngine" );

    return game;
} 
