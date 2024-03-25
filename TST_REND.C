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
	int timer[2] = {22, 16};
	void *base = Physbase();

	/* Sets the scene */
	render(&test_mso, timer, base);
	
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
				render(&test_mso, timer, base);
			}

			if (key == 'A' || key == 'a') {
				move_left_request(&(test_mso.reticle));
				render(&test_mso, timer, base);
			}

			if (key == 'S' || key == 's') {
				move_down_request(&(test_mso.reticle));
				render(&test_mso, timer, base);
			}

			if (key == 'D' || key == 'd') {
				move_right_request(&(test_mso.reticle));
				render(&test_mso, timer, base);
			}

			/* Clock tick, triggers all synchronous events */
			if (key == ' ') {
				timer[1] -= 1;

				/* second digit will not go below 0 */
				if (timer[1] < 16) {
					timer[1] += 10;
					timer[0] -= 1;
				}

				/* Check lose condition */
				if ((timer[0] == 16) && (timer[1] == 16)) {
					Cconws("YOU LOSE!\n\r");
					break;
				}

				mallard_move_request(&(test_mso.mallards[0]));
				mallard_move_request(&(test_mso.mallards[1]));
				render(&test_mso, timer, base);
			}

			/* Ends session */
			if (key == 'Q' || key == 'q') {
				break;
			}
		}
	}

	return 0;
} 