#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "MODEL.H"
#include "FONT.H"

const Model test_mso =
{
	{320, 200, 16, 19, 0, 0},	/* the Reticle; the player */
	{
		{49, 49, 16, 14, 0, 0},		    /* Mallard 1 */
		{591, 351, 16, 14, 0, 0}		/* Mallard 2 */
	}
};

int main()
{
    void *base = Physbase();

	clear_screen(base, 0);
	plot_bitmap_16(base, 320, 200, reticle_bitmap, 19);
	plot_bitmap_16(base, 49, 49, mallard_bitmap, 14);
	plot_bitmap_16(base, 591, 351, mallard_bitmap, 14);

	return 0;
} 