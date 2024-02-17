#ifndef RASTER_H
#define RASTER_H

#include "TYPES.H"

/* Prototypes */
void plot_pixel(UINT16 *base, int x, int y);
void plot_vertical_line(UINT16 *base, int x, int y, int length);
void plot_horizontal_line(UINT16 *base, int x, int y, int length);
void clear_screen(UINT16 *base, int pattern);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap,
                    unsigned int height);
/* extern void clear_screen(UINT32 *base); */
void plot_bitmap_8(UINT16 *base, int x, int y, const UINT16 *bitmap,
                   unsigned int height);
void plot_text(UINT16 *base, int x, int y, const UINT8 *bitmap, int ascii);


/* bitmaps */
extern const UINT16 reticle_bitmap[];
extern const UINT16 mallard_bitmap[];

#endif
