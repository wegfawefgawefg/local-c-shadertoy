#ifndef STATE_H
#define STATE_H

#include <stdbool.h>

#define GRID_SIZE 64

struct State
{
    bool quit;
    float grid[GRID_SIZE][GRID_SIZE]; // 64x64 grid of vertical offsets
};

#endif // STATE_H