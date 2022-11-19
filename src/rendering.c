#include "include/rendering.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "include/camera.h"
#include "include/vector.h"
#include "include/screen.h"
#include "include/map.h"

struct camera *init_camera(struct vect_2 *pos, struct screen *screen, struct map *map, int fov)
{
    struct camera *res = malloc(sizeof(struct camera));
    res->pos = pos;
    res->screen = screen;
    res->map = map;
    res->rays_count = screen->width;
    res->rays = calloc(sizeof(double), res->rays_count);
    for (size_t i = 0; i < res->rays_count; i++)
    {
        res->rays[i] = -fov / 2 + fov * (double)i / (double)res->rays_count;
    }
    return res;
}

void draw_ray(struct camera *camera, int x, double dist)
{
    int len = (int) dist == 0 ? camera->screen->height : (int)(100 / dist) % camera->screen->height;

    for (int i = 0; i < camera->screen->height; i++)
    {
        int min = camera->screen->height / 2 - len / 2;
        int max = camera->screen->height / 2 + len / 2;

        if (i < min || i > max)
        {
            put_pixel(camera->screen, x, i, ' ');
        }
        else
        {
            put_pixel(camera->screen, x, i, '#');
        }
    }
}

double get_dist(struct vect_2 *pos, struct vect_2 *dir, struct segment *segment)
{
    double x1 = pos->x;
    double y1 = pos->y;
    double x2 = pos->x + dir->x;
    double y2 = pos->y + dir->y;
    double x3 = segment->start.x;
    double y3 = segment->start.y;
    double x4 = segment->end.x;
    double y4 = segment->end.y;

    double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0)
    {
        return 0;
    }
    double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    if (t > 0 && t < 1 && u > 0)
    {
        return u;
    }
    return 0;
}

int compute_dist(struct vect_2 *pos, double ray, struct map *map)
{
    return rand() % 10;
    return 10 * ray * (ray < 0 ? -1 : 1);
    int min = -1;
    for (size_t i = 0; i < map->segment_count; i++)
    {
        struct segment *seg = &map->segments[i];
        struct vect_2 dir = {cos(ray), sin(ray)};
        double dist = get_dist(pos, &dir, seg);
        if (dist > 0 && (min == -1 || dist < min))
        {
            min = dist;
        }
    }
    return min;
}

void render(struct camera *camera)
{
    for (size_t i = 0; i < camera->rays_count; i++)
    {
        draw_ray(camera, i, compute_dist(camera->pos, camera->rays[i], camera->map));
    }
}