#pragma once

#include "renderer_types.hpp"

struct window;

bool renderer_backend_create(renderer_backend_type type, struct window* window, renderer_backend* out_renderer_backend);
void renderer_backend_destroy(renderer_backend* renderer_backend);