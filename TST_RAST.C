#include <osbind.h>
#include "RASTER.H"

const UINT16 reticle[19] =
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
	void *base = Physbase();

	/* clear_screen(base);
	plot_bitmap_16(base, 128, 300, mallard_bitmap, 14);
	plot_bitmap_16(base, 512, 300, reticle, 19); */

	clear_screen(base);
	plot_vertical_line(base, 128, 300, 99);
	plot_horizontal_line(base, 128, 300, 100);

	return 0;
}
