#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "EVENTS.H"
#include "RENDERER.H"
#include "INPUT.H"

#define BUFEER_A 0xFF8200
#define BUFFER_B 0xFA0000

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
	UINT32 count = 600;
	void *base = Physbase();

	/* Sets the scene */
	render(&test_mso, base);
	
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

            render(&test_mso, base);
		}

		clock_timer(&(count));
		printf("%lu seconds left \n\r", count/10);

		if (count < 1 || count > 600) {
			break;
		}
		
		}

	return 0;
} 