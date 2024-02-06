#include <osbind.h>
#include "raster.h"

const UINT16 mallard_bitmap[16] =
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
	0x0180,
	0x0180,
	0x0000,
	0x0000
};

int main()
{
	void *base = Physbase();

	plot_bitmap_16(base, 128, 300, mallard_bitmap, 16);
	/* _clear_screen(); */

	return 0;
}
