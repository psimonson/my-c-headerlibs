#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;
	int y;

	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;
	clear_BMP(bmp, 0xff, 0xff, 0xff);
	for (y=bmp->header.info.height-1; y >= 0; y-=10)
		draw_line_BMP(bmp, 1, 64, y, 255, 0, 0);
	write_BMP(bmp, 0);
	display_info_BMP(bmp);
	destroy_BMP(bmp);
	return 0;
}
