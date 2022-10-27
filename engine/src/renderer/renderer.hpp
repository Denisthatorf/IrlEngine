#pragma once 

#include <defines.hpp>

struct window;

enum class RendererType {
    Vulkan,
    OpenGL,
    DirectX
};

struct renderer
{
    //TODO: think
    virtual ~renderer() {};

    virtual bool initialize(const char* application_name, struct window* window) = 0;
    virtual void shutdown() = 0;

    virtual void resized(uint16_t width, uint16_t height) = 0;

    virtual bool begin_frame(float delta_time) = 0;
    virtual bool end_frame(float delta_time) = 0;    

    struct window* window;
    uint64_t frame_number;
};

struct render_packet {
    float delta_time;
};

bool renderer_initialize(const char* application_name, window* window);
void renderer_shutdown();

bool renderer_draw_frame(render_packet* packet);