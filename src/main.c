#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#include "include/screen.h"
#include "include/camera.h"
#include "include/vector.h"
#include "include/rendering.h"
#include "include/map.h"

int main(void)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    system("stty -icanon");

    struct screen *screen = init_screen(w.ws_col, w.ws_row-1);
    struct vect_2 *pos = malloc(sizeof(struct vect_2));
    pos->x = 0;
    pos->y = 0;

    struct map *map = init_map(10);
    add_line(5, -3, 5, 3, map);
    struct camera *camera = init_camera(pos, screen, map, 40);


    while (1)
    {

        display_screen(screen);
        render(camera);
        msleep(20);
    }


}