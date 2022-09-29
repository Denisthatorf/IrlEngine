#pragma once

#include <string>
#include <vector>

//TODO: custom vector
void window_get_required_extension_names(std::vector<const char*>& names);

bool window_create_vulkan_surface(
    struct window* plat_state,
    struct vulkan_context* context);