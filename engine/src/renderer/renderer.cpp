#include "renderer.hpp"
#include <renderer/vulkan/vulkan_renderer.hpp>

#include "core/logger.hpp"

static renderer* renderer;

bool renderer_initialize(const char* application_name, window* window)
{
    // TODO: make this configurable.
    renderer = new vulkan_renderer();

    if (!renderer->initialize(application_name, window)) {
        CORE_LOG_CRITICAL("Renderer backend failed to initialize. Shutting down.");
        return false;
    }

    return true;
}

void renderer_shutdown() {
    renderer->shutdown();

    //TODO: custom allocator delete
    delete renderer;
}

bool renderer_draw_frame(render_packet* packet) {
    // If the begin frame returned successfully, mid-frame operations may continue.
    if (renderer->begin_frame(packet->delta_time)) {

        // End the frame. If this fails, it is likely unrecoverable.
        bool result = renderer->end_frame(packet->delta_time);

        if (!result) {
            CORE_LOG_ERROR("renderer_end_frame failed. Application shutting down...");
            return false;
        }
    }

    return true;
}