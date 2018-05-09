#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;

	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;

	clear_BMP(bmp, 0, 0, 0);
	/* draw red star */
	draw_star_BMP(bmp, 0, 0, 20, 255, 0, 0);
	/* draw green star */
	draw_star_BMP(bmp, 1, 1, 20, 0, 255, 0);
	/* draw blue star */
	draw_star_BMP(bmp, 2, 2, 20, 0, 0, 255);
	/* write the bitmap */
	write_BMP(bmp, 0);
	/* cleanup bitmap */
	destroy_BMP(bmp);
	return 0;
}
