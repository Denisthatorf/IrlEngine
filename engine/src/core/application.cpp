#include "application.hpp"
#include "game_types.hpp"
#include "logger.hpp"
#include "window.hpp"

#include <utils/irl_general_allocator.hpp>

struct application_state {
    game* game_inst;
    bool is_running;
    bool is_suspended;
    //platform_state platform;
    int16_t width;
    int16_t height;
    float last_time;
};

static bool isInitialized = false;
static application_state app_state;

bool application_create(game* game_inst)
{
    if (isInitialized) 
    {
        CORE_LOG_ERROR("application_create called more than once.");
        return false;
    }

    app_state.game_inst = game_inst;

    // Initialize subsystems.
    app_state.is_running = true;
    app_state.is_suspended = false;
	
    initLogger();
	if(!initWindow(game_inst->app_config.start_width,
			game_inst->app_config.start_height,
			game_inst->app_config.name))
	{
		CORE_LOG_CRITICAL("Can't init window");
		return false;
	}

    // Initialize the game.
    if (!app_state.game_inst->initialize(app_state.game_inst)) {
        CORE_LOG_CRITICAL("Game failed to initialize.");
        return false;
    }

    isInitialized = true;

    return true;
}

#include <vector>

bool application_run() 
{
    while (app_state.is_running) 
    {
        if(!pollWindowEvents()) {
            app_state.is_running = false;
        }

        if(!app_state.is_suspended) {
            if (!app_state.game_inst->update(app_state.game_inst, (float)0)) {
                CORE_LOG_CRITICAL("Game update failed, shutting down.");
                app_state.is_running = false;
                break;
            }

            // Call the game's render routine.
            if (!app_state.game_inst->render(app_state.game_inst, (float)0)) {
                CORE_LOG_CRITICAL("Game render failed, shutting down.");
                app_state.is_running = false;
                break;
            }
        }
    }

    if(get_general_allocationsNow() > 0)
        CORE_LOG_WARN("Forger to deallocate smth");

    app_state.is_running = false;
	
	destroyWindow();
	shutdownLogger();

    return true;
} 
