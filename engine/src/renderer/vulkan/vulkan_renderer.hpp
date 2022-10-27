#pragma once

#include <renderer/renderer.hpp>

struct vulkan_renderer : public renderer
{
    bool initialize(const char* application_name, struct window* window) override;
    void shutdown() override;

    void resized(uint16_t width, uint16_t height) override;

    bool begin_frame(float delta_time) override;
    bool end_frame(float delta_time) override;

};