#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "EVENTS.H"
#include "RENDERER.H"

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
	int key;
	UINT32 timer = 45;
	void *base = Physbase();

	/* Sets the scene */
	render(&test_mso, base);
	
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
				render(&test_mso, base);
			}

			if (key == 'A' || key == 'a') {
				move_left_request(&(test_mso.reticle));
				render(&test_mso, base);
			}

			if (key == 'S' || key == 's') {
				move_down_request(&(test_mso.reticle));
				render(&test_mso, base);
			}

			if (key == 'D' || key == 'd') {
				move_right_request(&(test_mso.reticle));
				render(&test_mso, base);
			}

			/* Clock tick, triggers all synchronous events */
			if (key == ' ') {
				clock_timer(&timer);
				printf("Timer = %d\n", timer);

				/* Check lose condition */
				if (time_lose_check(timer)) {
					Cconws("YOU LOSE!\n\r");
					break;
				}

				mallard_move_request(&(test_mso.mallards[0]));
				mallard_move_request(&(test_mso.mallards[1]));
				render(&test_mso, base);
			}

			/* Ends session */
			if (key == 'Q' || key == 'q') {
				break;
			}
		}
	}

	return 0;
} 