#include <osbind.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

typedef unsigned int UINT16;

void plot_pixel(UINT16*, int, int);
void plot_vertical_line(UINT16*, int, int, int);

int main() {
    UINT16 *base = Physbase();

    return 0;
}

/* Plots a singular pixel at the x & y coordinate given */
void plot_pixel (UINT16* base, int x, int y) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
        *(base + y * 40 + (x >> 4)) |= 1 << 7 - (x & 7);
}

/* Plots first pixel at the x & y coordinate, then continues to plot a pixel below that coordinate */
void plot_vertical_line (UINT16* base, int x, int y, int length) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT - length) {
        plot_pixel(base, x, y);

        int row; /* This doesn't work */
        for (row = 0; row < length; row += 1) {
            y += 40;
            plot_pixel(base, x, y);
        }
    }
}