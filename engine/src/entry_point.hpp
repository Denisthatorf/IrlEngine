#pragma once

#include <core/application.hpp>
#include <core/logger.hpp>
#include <game_types.hpp>

extern Game* create_game();

/**
 * The main entry point of the application.
 */
int main(void) {
    Game* game_inst = create_game();

    // Initialization.
    if (!application_create(game_inst)) {
        CORE_LOG_DEBUG("Application failed to create!.");
        return 1;
    }

    // Begin the game loop.
    if(!application_run()) {
        CORE_LOG_DEBUG("Application did not shutdown gracefully.");
        return 2;
    }

    delete game_inst;

    return 0;
} 
