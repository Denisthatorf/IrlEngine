#pragma once

#include "renderer/renderer_backend.hpp"

bool vulkan_renderer_backend_initialize(renderer_backend* backend, const char* application_name, struct window* window);
void vulkan_renderer_backend_shutdown(renderer_backend* backend);

void vulkan_renderer_backend_on_resized(renderer_backend* backend, uint16_t width, uint16_t height);

bool vulkan_renderer_backend_begin_frame(renderer_backend* backend, float delta_time);
bool vulkan_renderer_backend_end_frame(renderer_backend* backend, float delta_time);