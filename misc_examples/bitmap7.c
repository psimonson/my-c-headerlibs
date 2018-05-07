#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;

	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;
	clear_BMP(bmp, 0xff, 0xff, 0xff);
	draw_line_BMP(bmp, 40, 20, 20, 255, 0, 0);
	write_BMP(bmp, 0);
	display_info_BMP(bmp);
	destroy_BMP(bmp);
	return 0;
}
