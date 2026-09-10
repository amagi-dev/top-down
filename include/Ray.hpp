#ifndef ___RAY_HPP___
#define ___RAY_HPP___

#include <iostream>
#include <assert.h>

namespace ray {
    #include <raylib.h>


    const int SCALE = 3;                        // Scale value
    const int TILE_SIZE_SCALED = 16 * SCALE;    // Apply scaling size
    const int TILE_SIZE = 16;                   // Original size
}

#endif
