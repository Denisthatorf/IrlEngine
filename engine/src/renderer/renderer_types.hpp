#pragma once

#include "defines.hpp"

enum renderer_backend_type {
    RENDERER_BACKEND_TYPE_VULKAN,
    RENDERER_BACKEND_TYPE_OPENGL,
    RENDERER_BACKEND_TYPE_DIRECTX
};

struct renderer_backend {
    struct window* window;
    uint64_t frame_number;

    bool (*initialize)(struct renderer_backend* backend, const char* application_name, struct window* window);

    void (*shutdown)(struct renderer_backend* backend);

    void (*resized)(struct renderer_backend* backend, uint16_t width, uint16_t height);

    bool (*begin_frame)(struct renderer_backend* backend, float delta_time);
    bool (*end_frame)(struct renderer_backend* backend, float delta_time);    
};

struct render_packet {
    float delta_time;
};