#include "RASTER.H"
#include "TYPES.H"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_SCREEN 32000

/*******************************************************************************
 * FUNCTION NAME: plot_pixel                                                   *
 *                                                                             *
 * INPUT: *base = pointer to the starting address of the frame buffer (FB)     *
 *          x = x - coordinate                                                 *
 *          y = y - coordinate                                                 *
 *                                                                             *
 * OUTPUT: no return value from function, FB at coordinate (x,y) is turned on  *
 *                                                                             *
 * ASSUMPTION:                                                                 *
 *                                                                             *
 *******************************************************************************/
void plot_pixel(UINT16 *base, int x, int y) {
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
    *(base + y * 40 + (x >> 4)) |= 1 << 15 - (x & 15);
}

/* Plots first pixel at the x & y coordinate, then continues to plot a pixel
     below that coordinate */
/*******************************************************************************
 * FUNCTION NAME: plot_vertical_line                                           *
 *                                                                             *
 * INPUT: *base = pointer to the starting address of the frame buffer (FB)     *
 *          x = x - coordinate                                                 *
 *          y = y - coordinate                                                 *
 *          length = length of the verticl line                                *
 *                                                                             *
 * OUTPUT: no return value from function, FB at coordinate (x,y)to(x,y+length) *
 *           is turned on.                                                     *
 *                                                                             *
 * ASSUMPTION:                                                                 *
 *                                                                             *
 *******************************************************************************/
void plot_vertical_line(UINT16 *base, int x, int y, int length) {
  int row;

  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT - length) {
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;

    for (row = 0; row < length; row++) {
      *loc |= 1 << 15 - (x & 15);
      loc += 40;
    }
  }
}

/*******************************************************************************
 * FUNCTION NAME: plot_horizontal_line                                         *
 *                                                                             *
 * INPUT: *base = pointer to the starting address of the frame buffer (FB)     *
 *          x = x - coordinate                                                 *
 *          y = y - coordinate                                                 *
 *          length = length of horizontal line                                 *
 * OUTPUT: no return value from function, FB at coordinate (x,y) is turned on  *
 *                                                                             *
 * ASSUMPTION:                                                                 *
 *                                                                             *
 *******************************************************************************/
/* Plots first pixel at the x & y coordinate, then continues to plot a pixel
 * below that coordinate */
void plot_horizontal_line(UINT16 *base, int x, int y, int length) {
  int row;

  if (x >= 0 && x < SCREEN_WIDTH - length && y >= 0 && y < SCREEN_HEIGHT) {
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int col;

    for (col = 0; col < length; col++) {
      *loc |= 1 << 15 - (x & 15);
      loc += 1;
    }
  }
}

/*******************************************************************************
 * FUNCTION NAME: clear_screen                                                 *
 *                                                                             *
 * INPUT: *base = pointer to the starting address of the frame buffer (FB)     *
 *          pattern = pattern of the desired outcome ot the screen             *
 *                                                                             *
 * OUTPUT: no return value from function, all 32kb of FB is filled with the    *
 *           pattern                                                           *
 *                                                                             *
 * ASSUMPTION:                                                                 *
 *                                                                             *
 *******************************************************************************/
/* Fills the whole screen with black or white, it assumes that the caller knows
 * that the pattern is based on 2's comp binary'*/
/* void clear_screen(UINT16 *base, int pattern) {
  register int i = 0;
  register UINT16 *loc = base;

  while (i++ < BYTES_PER_SCREEN) {
    *(loc++) = pattern;
  }
} */

/*******************************************************************************
 * FUNCTION NAME: plot_bitmap_16                                               *
 *                                                                             *
 * INPUT: *base = pointer to the starting address of the frame buffer (FB)     *
 *         x = x - coordinate                                                  *
 *         y = y - coordinate                                                  *
 *         bitmap = an array with hex codes that maps which bits to change     *
 *         height = determines when to stop placing rows                       *
 *                                                                             *
 * OUTPUT: no return value from function, all 32kb of FB is filled with the    *
 *           pattern                                                           *
 *                                                                             *
 * ASSUMPTION:                                                                 *
 *                                                                             *
 *******************************************************************************/
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
