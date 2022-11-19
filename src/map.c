#include "include/map.h"

#include <stdlib.h>

struct map *init_map(size_t capacity)
{
    struct map *map = malloc(sizeof(struct map));
    map->capacity = capacity;
    map->segment_count = 0;
    map->segments = calloc(sizeof(struct segment), capacity);
    return map;
}

void add_line(int x1, int y1, int x2, int y2, struct map *map)
{
    if (map->segment_count >= map->capacity)
    {
        return;
    }
    struct segment *seg = &map->segments[map->segment_count];
    seg->start.x = x1;
    seg->start.y = y1;
    seg->end.x = x2;
    seg->end.y = y2;
    map->segment_count++;
}