#include "irl_general_allocator.hpp"

#include <memory>
#include <stdio.h>

static size_t allAllocations;
static size_t allocationsNow;

size_t get_all_general_allocations() { return allAllocations; };
size_t get_general_allocationsNow() { return allocationsNow; };

void add_general_allocation_num(size_t numObjects) { allAllocations += numObjects; allocationsNow += numObjects; }
void minus_general_allocation_num(size_t numObjects) { allocationsNow -= numObjects; } 