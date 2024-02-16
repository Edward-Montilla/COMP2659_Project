#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "EVENTS.H"

Model test_mso =
{
	{320, 200, 16, 19, 0, 0},	/* the Reticle; the player */
	{
		{49, 49, 16, 14, 0, 0},		    /* Mallard 1 */
		{591, 351, 16, 14, 0, 0}		/* Mallard 2 */
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
	int timer = 45;
	void *base = Physbase();

	clear_screen(base, 0);
	plot_bitmap_16(base, 320, 200, reticle_bitmap, 19);
	plot_bitmap_16(base, 49, 49, mallard_bitmap, 14);
	plot_bitmap_16(base, 591, 351, mallard_bitmap, 14);
	
	Cconws("Press Q to Quit\n\r");
	Cconws("WASD to move\n\r");
	Cconws("Spacebar for clock tick\n\r");

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

			if (key == ' ') {
				game_timer(&timer);
				printf("Timer = %d\n", timer);

				mallard_move_request(&(test_mso.mallards[0]));
				printf("M1x = %d, ", test_mso.mallards[0].x);
				printf("M1y = %d\n", test_mso.mallards[0].y);

				mallard_move_request(&(test_mso.mallards[1]));
				printf("M2x = %d, ", test_mso.mallards[1].x);
				printf("M2y = %d\n", test_mso.mallards[1].y);
			}

			if (key == 'Q' || key == 'q') {
				break;
			}
		}
	}

	return 0;
} 