#ifndef RENDERING_H
#define RENDERING_H

#include "vector.h"
#include "screen.h"
#include "camera.h"

struct camera *init_camera(struct vect_2 *pos, struct screen *screen, struct map *map, int fov);

void draw_ray(struct camera *camera, int x, double dist);

void render(struct camera *camera);

#endif