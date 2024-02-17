#include "RENDERER.H"

/*******************************************************************************
 * FUNCTION NAME: render_reticle                                               *
 *                                                                             *
 * PURPOSE: Plots a raster graphic of the player's reticle.                    *   
 *                                                                             *
 * INPUT: *ret = a Reticle object that represents the player.                  *
 *                                                                             *
 * OUTPUT: no return value from function, plots a reticle on the screen.       *
 *                                                                             *
 * ASSUMPTION: reticle and base have been instantiated, and                    *
 *           the object's x and y are within bounds.                           *
 *                                                                             *
 *******************************************************************************/
void render_reticle(const Reticle *ret, UINT16 *base) {
    plot_bitmap_16(base, ret->x, ret->y, reticle_bitmap, ret->height);
}

/*******************************************************************************
 * FUNCTION NAME: render_mallard                                               *
 *                                                                             *
 * PURPOSE: Plots a raster graphic of a mallard.                               *   
 *                                                                             *
 * INPUT: *mallard = a Mallard object.                                         *
 *                                                                             *
 * OUTPUT: no return value from function, plots a mallard on the screen.       *
 *                                                                             *
 * ASSUMPTION: mallard and base have been instantiated, and                    *
 *           the object's x and y are within bounds.                           *
 *                                                                             *
 *******************************************************************************/
void render_mallard(const Mallard *mallard, UINT16 *base) {
    plot_bitmap_16(base, mallard->x, mallard->y, mallard_bitmap, mallard->height);
}