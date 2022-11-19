#ifndef SCREEN_H
#define SCREEN_H

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 48

struct screen {
    int width;
    int height;
    char *pixels;
};

int msleep(long msec);

void put_pixel(struct screen *screen, int x, int y, char val);

struct screen *init_screen(int width, int height);

void fill_random(struct screen *screen);

void display_screen(struct screen *screen);

#endif