#include "app_clock.hpp"
#include <platform/platform.hpp>

void app_clock::update() {
    if (this->start_time != 0) {
        this->elapsed = platform_get_absolute_time() - this->start_time;
    }
}

void app_clock::start() {
    this->start_time = platform_get_absolute_time();
    this->elapsed = 0;
}

void app_clock::stop() {
    this->start_time = 0;
}
