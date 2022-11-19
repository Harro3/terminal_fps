#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>

#include "vector.h"
#include "screen.h"

struct camera
{
    struct vect_2 *pos;
    struct screen *screen;
    struct map *map;

    size_t rays_count;
    double *rays;
};

#endif