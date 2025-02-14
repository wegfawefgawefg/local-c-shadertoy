#include "util.h"

// define rand_max as const
const int RAND_MAX = 32767;

float rand_range(float min, float max)
{
    // Generate a random float between 0 and 1
    float scale = rand() / (float)RAND_MAX;

    // Scale and shift it to the desired range
    return min + scale * (max - min);
}