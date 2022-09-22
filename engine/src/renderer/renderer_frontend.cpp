#include "renderer_frontend.hpp"

#include "renderer_backend.hpp"

#include "core/logger.hpp"

struct window;

// Backend render context.
static renderer_backend* backend = 0;

bool renderer_initialize(const char* application_name, struct window* window) {
    // TODO: custom allocation
    backend = new renderer_backend(); 

    // TODO: make this configurable.
    renderer_backend_create(RENDERER_BACKEND_TYPE_VULKAN, window, backend);
    backend->frame_number = 0;

    if (!backend->initialize(backend, application_name, window)) {
        CORE_LOG_CRITICAL("Renderer backend failed to initialize. Shutting down.");
        return false;
    }

    return true;
}

void renderer_shutdown() {
    backend->shutdown(backend);

    //TODO: custom allocator delete
    delete backend;
}

bool renderer_begin_frame(float delta_time) {
    return backend->begin_frame(backend, delta_time);
}

bool renderer_end_frame(float delta_time) {
    bool result = backend->end_frame(backend, delta_time);
    backend->frame_number++;
    return result;
}

bool renderer_draw_frame(render_packet* packet) {
    // If the begin frame returned successfully, mid-frame operations may continue.
    if (renderer_begin_frame(packet->delta_time)) {

        // End the frame. If this fails, it is likely unrecoverable.
        bool result = renderer_end_frame(packet->delta_time);

        if (!result) {
            CORE_LOG_ERROR("renderer_end_frame failed. Application shutting down...");
            return false;
        }
    }

    return true;
}