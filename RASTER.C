#include "RASTER.H"
#include "TYPES.H"
#include "FONT.H"

#include <stdio.h>

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
};

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
};

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
void plot_horizontal_line(UINT16 *base, int x, int y, int length) {
  if (x >= 0 && x < SCREEN_WIDTH - length && y >= 0 && y < SCREEN_HEIGHT) {
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int bit_offset = 15 - (x & 15);
    int col;

    for (col = 0; col < length; col++) {
      *loc |= 1 << bit_offset;
      x++;
      bit_offset = 15 - (x & 15);
      if (bit_offset == 15) loc += 1;
    }
  }
};

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
void clear_screen(UINT16 *base, int pattern) {
  register int i = 0;
  register UINT16 *loc = base;

  while (i++ < (BYTES_PER_SCREEN)/2 ) {
    *(loc++) = pattern;
  }
};

void plot_bitmap_32(UINT16 *base, int x, int y, const UINT16 *bitmap,
                    unsigned int height) {
  int i = 0;
  base += (x >> 4) + y * 40;

  while (i < height) {
    *base = bitmap[i] >> (x & 31);
    *(base + 1) = bitmap[i] << 32 - (x & 31);
    base += 40;
    i++;
  }
};


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
 *              Can only be displayed in address locations divible by 8        *
 *                                                                             *
 *******************************************************************************/
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap,
                    unsigned int height) {
  int i = 0;
  base += (x >> 4) + y * 40;

  while (i < height) {
    *base = bitmap[i] >> (x & 15);
    *(base + 1) = bitmap[i] << 16 - (x & 15);
    base += 40;
    i++;
  }
};

/*******************************************************************************
 * FUNCTION NAME: plot_bitmap_8                                                *
 *                                                                             *
 * PURPOSE: Plots a 8 x 8 size pixel bitmap at the specified coordinate        *
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
 *              Can only be displayed in address locations divible by 8        *
 *                                                                             *
 *******************************************************************************/
void plot_bitmap_8(UINT16 *base, int x, int y, const UINT16 *bitmap,
                   unsigned int height) {
  int i = 0;
  base += (x >> 3) + y * 80;

  while (i < height) {
    *base = bitmap[i] >> (x & 7);
    *(base + 1) = bitmap[i] << 8 - (x & 7);
    base += 80;
    i++;
  }
};

/*******************************************************************************
 * FUNCTION NAME: plot_text                                                *
 *                                                                             *
 * PURPOSE: Plots a 8 x 8 size pixel bitmap at the specified coordinate        *
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
 *              Can only be displayed in address locations divible by 8        *
 *                                                                             *
 *******************************************************************************/
void plot_text(UINT16 *base, int x, int y, const UINT8 *bitmap, int ascii) {
  UINT16 *loc = base + (y * 80) + (x >> 3);
  int row;
  /* subtract 32 from ascii value parameter */
  bitmap += ascii * 8; /* point to the letter */
  for (row = 0; row < 8; row++) {
    *loc |= bitmap[row];
    loc += 40;
  }
};

void plot_rectangle(UINT16 *base, int start_x, int start_y, int end_x, int end_y) {
  int row, col;
  UINT16 *loc;
  int bit_offset;
  printf("ugh");

  for (row = start_y; row < end_y; row++) {
    loc = base + (row * 40) + (start_x >> 4);
    bit_offset = 15 - (start_x & 15);

    printf("Row: %d, Memory Location: %p, Bit Offset: %d\n", row, loc, bit_offset);

    for (col = start_x; col < end_x; col++) {
      *loc |= 1 << bit_offset;
      bit_offset = (bit_offset - 1) & 15;
      if (bit_offset == 15) loc++;
    }
  }
};