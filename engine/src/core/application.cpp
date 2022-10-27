#include "application.hpp"
#include "game_types.hpp"

#include <utils/irl_general_allocator.hpp>

#include <core/logger.hpp>
#include <core/app_clock.hpp>

#include <platform/window.hpp>
#include <platform/platform.hpp>

#include <renderer/renderer.hpp>

struct application_state {
    Game* game_inst;
	window app_window;
    bool is_running;
    bool is_suspended;
    //platform_state platform;
    int16_t width;
    int16_t height;
    double last_time;
	app_clock clock;	
};

static bool isInitialized = false;
static application_state app_state;

bool application_create(Game* game_inst)
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
	if(!window_create(
			&app_state.app_window,
			game_inst->app_config.name,
			game_inst->app_config.start_pos_x,
			game_inst->app_config.start_pos_y,
			game_inst->app_config.start_width,
			game_inst->app_config.start_height))
	{
		CORE_LOG_CRITICAL("Can't init window");
		return false;
	}

    if (!renderer_initialize(game_inst->app_config.name, &app_state.app_window)) {
        CORE_LOG_CRITICAL("Failed to initialize renderer. Aborting application.");
        return false;
    }

    // Initialize the game.
    if (!app_state.game_inst->Initialize()) {
        CORE_LOG_CRITICAL("Game failed to initialize.");
        return false;
    }

    isInitialized = true;

    return true;
}

bool application_run() 
{
	app_state.clock.start();	
	app_state.clock.update();
	app_state.last_time = app_state.clock.elapsed;
	double running_time = 0;
	double frame_count = 0;
	double target_frame_seconds = 1.0f / 60;

    while (app_state.is_running) 
    {
		app_state.clock.update();
        double current_time = app_state.clock.elapsed;
        double delta = (current_time - app_state.last_time);
        double frame_start_time = platform_get_absolute_time();

        if(!window_pollWindowEvents(&app_state.app_window)) {
            app_state.is_running = false;
        }

        if(!app_state.is_suspended)
		{
            if (!app_state.game_inst->Update(delta)) 
			{
                CORE_LOG_CRITICAL("Game update failed, shutting down.");
                app_state.is_running = false;
                break;
            }

            if (!app_state.game_inst->Render(delta))
			{
                CORE_LOG_CRITICAL("Game render failed, shutting down.");
                app_state.is_running = false;
                break;
            }

			double frame_end_time = platform_get_absolute_time();
            double frame_elapsed_time = frame_end_time - frame_start_time;
            running_time += frame_elapsed_time;
            double remaining_seconds = target_frame_seconds - frame_elapsed_time;

            if (remaining_seconds > 0) 
			{
                uint64_t remaining_ms = (remaining_seconds * 1000);

                // If there is time left, give it back to the OS.
                bool limit_frames = false;
                if (remaining_ms > 0 && limit_frames)
				{
                    platform_sleep(remaining_ms - 1);
                }

                frame_count++;
            }

			//TODO: update input
			app_state.last_time = current_time;
        }
    }


    app_state.is_running = false;
	
	window_destroy(&app_state.app_window);
    renderer_shutdown();
	shutdownLogger();

    if(get_general_allocationsNow() > 0)
        CORE_LOG_WARN("Forger to deallocate smth");
        
    return true;
} 
