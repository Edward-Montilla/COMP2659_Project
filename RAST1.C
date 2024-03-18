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
    plot_text(base, 0, 0, font, 52);
    plot_text(base, 8, 0, font, 41);
    plot_text(base, 16, 0, font, 45);
    plot_text(base, 24, 0, font, 37);
    plot_text(base, 32, 0, font, 50);
    plot_text(base, 40, 0, font, 26);
    plot_text(base, 16, 10, font, 22);
    plot_text(base, 24, 10, font, 16);
	plot_bitmap_16(base, 320, 200, reticle_bitmap, 19);
	plot_bitmap_16(base, 49, 49, mallard_bitmap, 14);
	plot_bitmap_16(base, 591, 351, mallard_bitmap, 14);

	return 0;
} 