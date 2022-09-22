#include "renderer_backend.hpp"

#include "vulkan/vulkan_backend.hpp"

bool renderer_backend_create(renderer_backend_type type, struct window* window, renderer_backend* out_renderer_backend) {
    out_renderer_backend->window = window;

    if (type == RENDERER_BACKEND_TYPE_VULKAN) {
        out_renderer_backend->initialize = vulkan_renderer_backend_initialize;
        out_renderer_backend->shutdown = vulkan_renderer_backend_shutdown;
        out_renderer_backend->begin_frame = vulkan_renderer_backend_begin_frame;
        out_renderer_backend->end_frame = vulkan_renderer_backend_end_frame;
        out_renderer_backend->resized = vulkan_renderer_backend_on_resized;
        
        return true;
    }

    return false;
}

void renderer_backend_destroy(renderer_backend* renderer_backend) {
    renderer_backend->initialize = 0;
    renderer_backend->shutdown = 0;
    renderer_backend->begin_frame = 0;
    renderer_backend->end_frame = 0;
    renderer_backend->resized = 0;
}