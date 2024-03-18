#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "EVENTS.H"
#include "RENDERER.H"
#include "INPUT.H"

#define BUFEER_A 0xFF8200
#define BUFFER_B 0xFA7D00

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
	UINT32 count = 60000;
	UINT32 last_count = count;
	void *base_A = Physbase();
	void *base_B = (UINT16 *)Physbase() + BUFFER_B;

	/* Sets the scene */
	render(&test_mso, base_A);
	render(&test_mso, base_B);
	
	/* Instructions */
	Cconws("Press Q to Quit\n\r");
	Cconws("WASD to move\n\r");
	Cconws("Spacebar for clock tick\n\r");
	printf("you have %lu seconds left \n\r", count);

	while (1) {
		if (Cconis() != 0) {
			key = Cnecin();
			/* Ends session */
			if (key == 'q') {
				break;
			}

			read_key(key, &(test_mso.reticle));
		}
		
		clock_timer(&(count));

		/* move enemies */
		mallard_move_request(&(test_mso.mallards[0]));
		mallard_move_request(&(test_mso.mallards[1]));

		/* switch frame buffers*/
		if (count % 2 == 0) {
			Setscreen(-1, base_B, -1);
			render(&test_mso, base_A);
		} else {
			Setscreen(-1, base_A, -1);
			render(&test_mso, base_B);
		}
		
	}

	Setscreen(-1, base_A, -1);

	return 0;
} 