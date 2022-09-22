#pragma once
#include "renderer_types.hpp"

struct static_mesh_data;
struct window;

bool renderer_initialize(const char* application_name, struct window* window);
void renderer_shutdown();

void renderer_on_resized(uint16_t width, uint16_t height);

bool renderer_draw_frame(render_packet* packet);