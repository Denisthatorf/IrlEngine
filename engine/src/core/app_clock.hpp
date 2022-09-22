#pragma once 
#include <defines.hpp>

struct app_clock
{
    void start();
    void update();
    void stop();
    
    double start_time;
    double elapsed;
};
