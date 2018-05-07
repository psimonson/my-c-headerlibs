#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;

	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;

	clear_BMP(bmp, 0, 0, 0);
	/* center square */
	draw_square_BMP(bmp, 20, 20, 40, 40, 0, 255, 0);
	/* outter edge squares */
	draw_square_BMP(bmp, 0, 0, 20, 20, 0, 0, 255);
	draw_square_BMP(bmp, 40, 40, 63, 63, 255, 0, 0);
	write_BMP(bmp, 0);
	destroy_BMP(bmp);
	return 0;
}
