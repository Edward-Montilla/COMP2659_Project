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
	UINT32 last_count;
	UINT32 count = 60000;
	void *base_A = Physbase();
	void *base_B = (UINT16 *)Physbase() + BUFFER_B;

	if (base_B == NULL) {
		printf("naur");
		return 1;
	}

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

		/*
		last_count = count;
		clock_timer(&(count));

		if (last_count/1000 != count/1000) {
			printf("%lu seconds left \n\r", count/1000);
		}

		if (count < 1 || count > 60000) {
			break;
		}

		*/
		
		clock_timer(&(count));

		if (count % 2 == 0) {
			/* render(&test_mso, base_B); */
			Setscreen(-1, base_B, -1);
			render(&test_mso, base_A);
		} else {
			/* render(&test_mso, base_A); */
			Setscreen(-1, base_A, -1);
			render(&test_mso, base_B);
		}
		
		}

		Setscreen(-1, base_A, -1);

	return 0;
} 