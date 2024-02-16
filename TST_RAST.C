#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "EVENTS.H"

Model test_mso =
{
	{320, 200, 16, 19, 0, 0},	/* the Reticle; the player */
	{
		{208, 300, 16, 14, 0, 0},		/* Mallard 1 */
		{480, 300, 16, 14, 0, 0}		/* Mallard 2*/
	}
};

const UINT16 reticle_bitmap[19] =
{
	0x0180,
	0x0180,
	0x0180,
	0x0180,
	0x0180,
	0x0180,
	0x0000,
	0x0000,
	0xF99F,
	0xF99F,
	0xF99F,
	0x0000,
	0x0000,
	0x0180,
	0x0180,
	0x0180,
	0x0180,
	0x0180,
	0x0180
};

const UINT16 mallard_bitmap[14] =
{
	0x0000,
	0x0000,
	0x7FFE,
	0x7FFE,
	0x7FFE,
	0x7FFE,
	0x7FFE,
	0x0180,
	0x0180,
	0x0180,
	0x0180,
	0x0180,
	0x0000,
	0x0000
};

int main()
{
	int key;
	void *base = Physbase();

	clear_screen(base, 0);
	plot_bitmap_16(base, 320, 200, reticle_bitmap, 19);
	plot_bitmap_16(base, 208, 300, mallard_bitmap, 14);
	plot_bitmap_16(base, 480, 300, mallard_bitmap, 14);
	
	Cconws("Press Q to Quit\n\r");
	Cconws("WASD to move\n\r");

	while (1) {
		if (Cconis() != 0) {
			key = Cnecin();

			if (key == 'W' || key == 'w') {
				move_up_request(&(test_mso.reticle));
				printf("x = %d, ", test_mso.reticle.x);
				printf("y = %d\n", test_mso.reticle.y);
			}

			if (key == 'A' || key == 'a') {
				move_left_request(&(test_mso.reticle));
				printf("x = %d, ", test_mso.reticle.x);
				printf("y = %d\n", test_mso.reticle.y);
			}

			if (key == 'S' || key == 's') {
				move_down_request(&(test_mso.reticle));
				printf("x = %d, ", test_mso.reticle.x);
				printf("y = %d\n", test_mso.reticle.y);
			}

			if (key == 'D' || key == 'd') {
				move_right_request(&(test_mso.reticle));
				printf("x = %d, ", test_mso.reticle.x);
				printf("y = %d\n", test_mso.reticle.y);
			}

			if (key == 'Q' || key == 'q') {
				break;
			}
		}
	}

	return 0;
} 