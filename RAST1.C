#include <osbind.h>
#include <stdio.h>
#include "RENDERER.H"

const Model test_mso =
{
	{320, 200, 16, 19, 0, 0},	/* the Reticle; the player */
	{
		{49, 49, 16, 14, 0, 0},		    /* Mallard 1 */
		{591, 351, 16, 14, 0, 0}		/* Mallard 2 */
	}
};

/*
T = plot_text(base, 0, 0, font, 52);
I = plot_text(base, 8, 0, font, 41);
M = plot_text(base, 16, 0, font, 45);
E = plot_text(base, 24, 0, font, 37);
R = plot_text(base, 32, 0, font, 50);
: = plot_text(base, 40, 0, font, 26);
*/

int main()
{
	int key;
    void *base = Physbase();
	Cconws("Press 0-7 to render frames \n\r");
	Cconws("Press Q to quit");

	while (1) {
		if (Cconis() != 0) {
			key = Cnecin();

			/* Ends session */
			if (key == 'q') {
				break;
			}

			switch (key)
			{
			case '0':
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
				plot_bitmap_16(base, 49, 49, clay_pigeon_1, 14);
				plot_bitmap_16(base, 591, 351, clay_pigeon_2, 14);
				break;
			case '1':
				clear_screen(base, 0);
				plot_text(base, 0, 0, font, 52);
				plot_text(base, 8, 0, font, 41);
				plot_text(base, 16, 0, font, 45);
				plot_text(base, 24, 0, font, 37);
				plot_text(base, 32, 0, font, 50);
				plot_text(base, 40, 0, font, 26);
				plot_text(base, 16, 10, font, 20);
				plot_text(base, 24, 10, font, 19);
				plot_bitmap_16(base, 400, 150, reticle_bitmap, 19);
				plot_bitmap_16(base, 70, 150, clay_pigeon_4, 14);
				plot_bitmap_16(base, 500, 300, clay_pigeon_dead, 14);
				break;
			case '2':
				clear_screen(base, 0);
				plot_text(base, 0, 0, font, 52);
				plot_text(base, 8, 0, font, 41);
				plot_text(base, 16, 0, font, 45);
				plot_text(base, 24, 0, font, 37);
				plot_text(base, 32, 0, font, 50);
				plot_text(base, 40, 0, font, 26);
				plot_text(base, 16, 10, font, 18);
				plot_text(base, 24, 10, font, 21);
				plot_bitmap_16(base, 460, 40, reticle_bitmap, 19);
				plot_bitmap_16(base, 600, 62, clay_pigeon_3, 14);
				plot_bitmap_16(base, 422, 322, clay_pigeon_1, 14);
				break;
			case '3':
				clear_screen(base, 0);
				plot_text(base, 0, 0, font, 52);
				plot_text(base, 8, 0, font, 41);
				plot_text(base, 16, 0, font, 45);
				plot_text(base, 24, 0, font, 37);
				plot_text(base, 32, 0, font, 50);
				plot_text(base, 40, 0, font, 26);
				plot_text(base, 16, 10, font, 16);
				plot_text(base, 24, 10, font, 16);
				plot_bitmap_16(base, 60, 84, reticle_bitmap, 19);
				plot_bitmap_16(base, 321, 224, clay_pigeon_3, 14);
				plot_bitmap_16(base, 480, 380, clay_pigeon_dead, 14);
				break;
			case '4':
				clear_screen(base, 0);
				plot_text(base, 0, 0, font, 52);
				plot_text(base, 8, 0, font, 41);
				plot_text(base, 16, 0, font, 45);
				plot_text(base, 24, 0, font, 37);
				plot_text(base, 32, 0, font, 50);
				plot_text(base, 40, 0, font, 26);
				plot_text(base, 16, 10, font, 19);
				plot_text(base, 24, 10, font, 18);
				plot_bitmap_16(base, 600, 220, reticle_bitmap, 19);
				plot_bitmap_16(base, 600, 320, clay_pigeon_2, 14);
				plot_bitmap_16(base, 24, 382, clay_pigeon_2, 14);
				break;
			case '5':
				clear_screen(base, 0);
				plot_text(base, 0, 0, font, 52);
				plot_text(base, 8, 0, font, 41);
				plot_text(base, 16, 0, font, 45);
				plot_text(base, 24, 0, font, 37);
				plot_text(base, 32, 0, font, 50);
				plot_text(base, 40, 0, font, 26);
				plot_text(base, 16, 10, font, 21);
				plot_text(base, 24, 10, font, 25);
				plot_bitmap_16(base, 242, 110, reticle_bitmap, 19);
				plot_bitmap_16(base, 240, 116, clay_pigeon_4, 14);
				plot_bitmap_16(base, 28, 212, clay_pigeon_1, 14);
				break;
			case '6':
				clear_screen(base, 0);
				plot_text(base, 0, 0, font, 52);
				plot_text(base, 8, 0, font, 41);
				plot_text(base, 16, 0, font, 45);
				plot_text(base, 24, 0, font, 37);
				plot_text(base, 32, 0, font, 50);
				plot_text(base, 40, 0, font, 26);
				plot_text(base, 16, 10, font, 21);
				plot_text(base, 24, 10, font, 24);
				plot_bitmap_16(base, 238, 110, reticle_bitmap, 19);
				plot_bitmap_16(base, 240, 120, clay_pigeon_dead, 14);
				plot_bitmap_16(base, 32, 216, clay_pigeon_1, 14);
				break;
			case '7':
				clear_screen(base, 0);
				plot_text(base, 0, 0, font, 52);
				plot_text(base, 8, 0, font, 41);
				plot_text(base, 16, 0, font, 45);
				plot_text(base, 24, 0, font, 37);
				plot_text(base, 32, 0, font, 50);
				plot_text(base, 40, 0, font, 26);
				plot_text(base, 16, 10, font, 20);
				plot_text(base, 24, 10, font, 23);
				plot_bitmap_16(base, 620, 0, reticle_bitmap, 19);
				plot_bitmap_16(base, 620, 380, clay_pigeon_4, 14);
				plot_bitmap_16(base, 0, 380, clay_pigeon_1, 14);
				break;
			default:
				break;
			}
		}
	}

	return 0;
} 