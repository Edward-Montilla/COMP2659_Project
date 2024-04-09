#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "EVENTS.H"
#include "RENDERER.H"
#include "INPUT.H"
#include "MODEL.H"
#include "ISR.H"


#define BUFEER_A 0xFF8200L
#define BUFFER_B 0xFA7D00L

#define Cursor_off (printf("\033f"),fflush(stdout))
#define Curson_on (printf("\033e"),fflush(stdout))



const Model test_mso =
{
	{320, 200, 16, 19, 0, 0},	/* the Reticle; the player */
	{
		{49, 49, 16, 14, 0, 0, 0},		    /* Mallard 1 */
		{591, 351, 16, 14, 0, 0, 0}		/* Mallard 2 */
	}
};

int time_value[2] = {22, 16};


int main()
{
	int key;
	UINT32 count = 0;
	UINT32 last_count = count;


	void *base_A = Physbase();
	void *base_B = (UINT16 *)Physbase() + BUFFER_B;


	Cursor_off;
	
	plot_screen(base_A, starter_splashscreen);
	while (1) {
		if (Cconis() != 0) {
			key = Cnecin();
			/* Ends session */
			if (key == 'q') {
				break;
			}
		}
	}
	

	/* Sets the scene */
	render(&test_mso, time_value, base_A);
	render(&test_mso, time_value, base_B);
	
	/* Instructions */
	Cconws("Press Q to Quit\n\r");
	Cconws("WASD to move\n\r");
	Cconws("Spacebar for clock tick\n\r");
	printf("you have %lu seconds left \n\r", count/10);

	
	while (1) {

		/***** Asynchronous *****/
		if (Cconis() != 0) {
			key = Cnecin();
			/* Ends session */
			if (key == 'q') {
				break;
			}

			read_key(key, &(test_mso));
		}

		
		clock_timer(&(count));

		if (last_count%10 == count%10) {
			time_value[1] -= 1;

			/* second digit will not go below 0 */
			if (time_value[1] < 16) {
				time_value[1] += 10;
				time_value[0] -= 1;
			}
		}

		/* move enemies */

		mallard_move_request(&(test_mso.mallards[0]));
		mallard_move_request(&(test_mso.mallards[1]));
		

		/* switch frame buffers */
		if (count % 2 == 0) {
			Setscreen(-1, base_B, -1);
			render(&test_mso, time_value, base_A);
		} else {
			Setscreen(-1, base_A, -1);
			render(&test_mso, time_value, base_B);
		}


		if (time_lose_check(count) || shoot_win_check(&(test_mso.mallards[0]), &(test_mso.mallards[1]))) break;
	}
	
	/* game loop is over, returning the Atari ST to it's original state */

	Setscreen(-1, base_A, -1);

	Curson_on;

	return 0;
} 