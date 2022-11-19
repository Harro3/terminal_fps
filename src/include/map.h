#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

#include "vector.h"

struct segment
{
    struct vect_2 start;
    struct vect_2 end;
};

struct map
{
    size_t segment_count;
    size_t capacity;
    struct segment *segments;
};

struct map *init_map(size_t capacity);

void add_line(int x1, int y1, int x2, int y2, struct map *map);

#endif