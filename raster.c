#include <osbind.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_SCREEN 32000
#define BLACK_SCREEN -1
#define WHITE_SCREEN 0
#define INVADER_HEIGHT 16

typedef unsigned int UINT16;

void plot_pixel(UINT16 *base, int x, int y);
void plot_vertical_line(UINT16 *base, int x, int y, int length);
void plot_horizontal_line(UINT16 *base, int x, int y, int length);
void clear_screen(UINT16 *base, int pattern);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap,
                    unsigned int height);

const UINT16 invader_bitmap[INVADER_HEIGHT] = {
    0x0000, 0x0810, 0x0810, 0x0420, 0x0240, 0x1FF8, 0x2004, 0x4662,
    0x4002, 0x43C2, 0x2424, 0x1008, 0x0FF0, 0x0240, 0x0E70, 0x0000};

int main() {
  int x, y;
  UINT16 *base = Physbase();

  plot_vertical_line(base, 128, 0, 399);

  plot_horizontal_line(base, 0, 200, 639);

  for (y = 0; y < SCREEN_HEIGHT; y += INVADER_HEIGHT)
    for (x = 0; x < SCREEN_WIDTH; x += sizeof(UINT16))
      plot_bitmap_16(base, x, y, invader_bitmap, INVADER_HEIGHT);

  clear_screen(base, WHITE_SCREEN);

  return 0;
}

/* Plots a singular pixel at the x & y coordinate given */ void
plot_pixel(UINT16 *base, int x, int y) {
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
    *(base + y * 40 + (x >> 4)) |= 1 << 15 - (x & 15);
}

/* Plots first pixel at the x & y coordinate, then continues to plot a pixel
     below that coordinate */
void plot_vertical_line(UINT16 *base, int x, int y, int length) {
  int row;

  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT - length) {
    plot_pixel(base, x, y);

    for (row = 0; row < length; row++) {
      y += 1;
      plot_pixel(base, x, y);
    }
  }
}

/* Plots first pixel at the x & y coordinate, then continues to plot a pixel
 * below that coordinate */
void plot_horizontal_line(UINT16 *base, int x, int y, int length) {
  int row;

  if (x >= 0 && x < SCREEN_WIDTH - length && y >= 0 && y < SCREEN_HEIGHT) {
    plot_pixel(base, x, y);

    for (row = 0; row < length; row++) {
      x += 1;
      plot_pixel(base, x, y);
    }
  }
}

/* Fills the whole screen with black or white, it assumes that the caller knows
 * that the pattern is based on 2's comp binary'*/
void clear_screen(UINT16 *base, int pattern) {
  register int i = 0;
  register UINT16 *loc = base;

  while (i++ < BYTES_PER_SCREEN) {
    *(loc++) = pattern;
  }
}

/* plots a 16 x 16 bitmap on coordinantes that are within the bounds of the
 * screen */
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap,
                    unsigned int height) {
  UINT16 *loc = base + (y * 40) + (x >> 4);
  int row;

  for (row = 0; row < height; row++) {
    *loc |= bitmap[row]; /* danger (no bounds checking!) */
    loc += 40;           /* 40 is the number of words between the current */
  }
}
