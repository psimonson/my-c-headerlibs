#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;

	/* create bitmap 64x64x24 */
	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;

	/* initialise bitmap to black background */
	clear_BMP(bmp, 0, 0, 0);
	/* draw blue circle */
	draw_circle_BMP(bmp, 10, -35, 20, 0, 0, 255);
	/* draw red square */
	draw_square_BMP(bmp, 32, 30, 20, 255, 0, 0);
	/* draw green square */
	draw_square_BMP(bmp, 12, 30, 20, 0, 255, 0);
	/* draw yellow square */
	draw_square_BMP(bmp, 12, 10, 20, 0, 255, 255);
	/* draw pink square */
	draw_square_BMP(bmp, 32, 10, 20, 255, 0, 255);
	write_BMP(bmp, 0);
	destroy_BMP(bmp);
	return 0;
}
