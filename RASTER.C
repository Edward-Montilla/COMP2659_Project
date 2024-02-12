#include "RASTER.H"
#include "TYPES.H"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_SCREEN 32000

/*******************************************************************************
 * FUNCTION NAME: plot_pixel                                                   *
 *                                                                             *
 * PURPOSE: Plot a signular pixel at the given coordinate                      *
 *                                                                             *
 * INPUT: *base = pointer to the starting address of the frame buffer (FB)     *
 *          x = x - coordinate                                                 *
 *          y = y - coordinate                                                 *
 *                                                                             *
 * OUTPUT: no return value from function, FB at coordinate (x,y) is turned on  *
 *                                                                             *
 * ASSUMPTION: Ploting in done as a whole byte, and is OR masked.              *
 *              leaves neighboring pixels unaffected                           *
 *                                                                             *
 *******************************************************************************/
void plot_pixel(UINT16 *base, int x, int y) {
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
    *(base + y * 40 + (x >> 4)) |= 1 << 15 - (x & 15);
}


/*******************************************************************************
 * FUNCTION NAME: plot_vertical_line                                           *
 *                                                                             *
 * PURPOSE:  uses a for loop to plot a vertical line at the specified          *
 *           coordinates with the specified length                             *
 *                                                                             *
 * INPUT: *base = pointer to the starting address of the frame buffer (FB)     *
 *          x = x - coordinate                                                 *
 *          y = y - coordinate                                                 *
 *          length = length of the verticl line                                *
 *                                                                             *
 * OUTPUT: no return value from function, FB at coordinate (x,y)to(x,y+length) *
 *           is turned on.                                                     *
 *                                                                             *
 * ASSUMPTION: Vertical line begins at the coordinate and ends at (x + length).*
 *             Plots first pixel at the x & y coordinate, then continues       *
 *             to plot a pixel below that coordinate                           *
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
 * PURPOSE: Uses a for loop to plot a horizontal line at the                   * 
 *          specified coordinate with the specified length                     *
 *                                                                             *
 * INPUT: *base = pointer to the starting address of the frame buffer (FB)     *
 *          x = x - coordinate                                                 *
 *          y = y - coordinate                                                 *
 *          length = length of horizontal line                                 *
 * OUTPUT: no return value from function, FB at coordinate (x,y) is turned on  *
 *                                                                             *
 * ASSUMPTION: Horizontal line begins at coordinate and ends in (y + length).  *
 *              Plots first pixel at the x & y coordinate, then continues to   *
 *              plot a pixel below that coordinate                             *
 *                                                                             *
 *******************************************************************************/
/* */
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
 * PURPOSE: fills the screen with black or white according to pattern argument *
 *                                                                             * 
 * INPUT: *base = pointer to the starting address of the frame buffer (FB)     *
 *          pattern = pattern of the desired outcome ot the screen             *
 *                                                                             *
 * OUTPUT: no return value from function, all 32kb of FB is filled with the    *
 *           pattern                                                           *
 *                                                                             *
 * ASSUMPTION: Not as optimized as it can be, good enough to transition        *
 *                                                                             *
 *******************************************************************************/
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
 * PURPOSE: Plots a 16 x 16 size pixel bitmap at the specified coordinate      *   
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
 * ASSUMPTION: Bounds are checked to be within the size of the bitmap.         *
 *                                                                             *
 *******************************************************************************/
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap,
                    unsigned int height) {
  UINT16 *loc = base + (y * 40) + (x >> 4);
  int row;

  for (row = 0; row < height; row++) {
    *loc |= bitmap[row]; /* needs bounds checking */
    loc += 40;  /* 40 is the number of 'word'(s) between the current pixel and the pixel directly bellow it */
  }
}
