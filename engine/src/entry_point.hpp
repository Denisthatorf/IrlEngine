#pragma once

#include <core/application.hpp>
#include <core/logger.hpp>
#include <game_types.hpp>

// Externally-defined function to create a game.
extern bool create_game(game* out_game);

/**
 * The main entry point of the application.
 */
int main(void) {
    // Request the game instance from the application.
    game game_inst;
    if (!create_game(&game_inst)) {
        CORE_LOG_CRITICAL("Could not create game!");
        return -1;
    }

    // Ensure the function pointers exist.
    if (!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.on_resize) {
        CORE_LOG_CRITICAL("The game's function pointers must be assigned!");
        return -2;
    }

    // Initialization.
    if (!application_create(&game_inst)) {
        CORE_LOG_DEBUG("Application failed to create!.");
        return 1;
    }

    // Begin the game loop.
    if(!application_run()) {
        CORE_LOG_DEBUG("Application did not shutdown gracefully.");
        return 2;
    }

    return 0;
} 
