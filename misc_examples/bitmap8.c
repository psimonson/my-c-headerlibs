#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;

	/* create a BMP file width/height (60x60x24bpp) */
	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;

	clear_BMP(bmp, 255, 255, 255);
	draw_circle_BMP(bmp, 10, -25, 20, 255, 0, 0);
	write_BMP(bmp, 0);
	destroy_BMP(bmp);
	return 0;
}
