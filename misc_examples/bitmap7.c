#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;

	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;

	clear_BMP(bmp, 255, 255, 255);
	draw_line_BMP(bmp, 0, 0, 64, 64, 255, 0, 0);
	write_BMP(bmp, 0);
	destroy_BMP(bmp);
	return 0;
}
