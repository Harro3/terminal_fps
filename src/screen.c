#define _POSIX_C_SOURCE 200809L

#include "include/screen.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

struct screen *init_screen(int width, int height)
{
    
    struct screen *screen = malloc(sizeof(struct screen));
    screen->width = width;
    screen->height = height;
    screen->pixels = calloc((width+1) * height, sizeof(char));
    for (int i = 0; i < screen->height; i++) {
    screen->pixels[i * (screen->width+1) + screen->width] = '\n';
    }
    return screen;
}

void put_pixel(struct screen *screen, int x, int y, char val)
{
    screen->pixels[y * (screen->width + 1)+x] = val;
}

void fill_random(struct screen *screen)
{
    for (int i = 0; i < screen->height; i++)
    {
        for (int j = 0; j < screen->width; j++)
        {
            put_pixel(screen, j, i, rand() % 2 == 0 ? '#' : 'O');
        }
    }
}
void display_screen(struct screen *screen)
{
    write(STDOUT_FILENO, screen->pixels, (screen->width+1)*screen->height);
}