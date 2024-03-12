#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "EVENTS.H"
#include "RENDERER.H"
#include "INPUT.H"

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
	int timer = 45;
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
			/* Ends session */
			if (key == 'Q' || key == 'q') {
				break;
			}

			read_key(key, &(test_mso.reticle));

            render(&test_mso, base);
		}
	}

	return 0;
} 