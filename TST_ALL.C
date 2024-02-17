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

int main()
{
	int key;
	int timer = 45;
	void *base = Physbase();

	/* Sets the scene */
	clear_screen(base, 0);
	plot_bitmap_16(base, 320, 200, reticle_bitmap, 19);
	plot_bitmap_16(base, 49, 49, mallard_bitmap, 14);
	plot_bitmap_16(base, 591, 351, mallard_bitmap, 14);
	
	/* Instructions */
	Cconws("Press Q to Quit\n\r");
	Cconws("WASD to move\n\r");
	Cconws("Spacebar for clock tick\n\r");

	while (1) {
		if (Cconis() != 0) {
			key = Cnecin();

			/* Player Movement */
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

			/* Clock tick, triggers all synchronous events */
			if (key == ' ') {
				game_timer(&timer);
				printf("Timer = %d\n", timer);

				/* Check lose condition */
				if (time_lose_check(timer)) {
					Cconws("YOU LOSE!\n\r");
					break;
				}

				mallard_move_request(&(test_mso.mallards[0]));
				printf("M1x = %d, ", test_mso.mallards[0].x);
				printf("M1y = %d\n", test_mso.mallards[0].y);

				mallard_move_request(&(test_mso.mallards[1]));
				printf("M2x = %d, ", test_mso.mallards[1].x);
				printf("M2y = %d\n", test_mso.mallards[1].y);
			}

			/* Ends session */
			if (key == 'Q' || key == 'q') {
				break;
			}
		}
	}

	return 0;
} 