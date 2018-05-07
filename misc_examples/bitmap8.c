#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;
	int i;

	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;

	clear_BMP(bmp, 255, 255, 255);
	for (i=1; i < 2; i++) {
		draw_hline_BMP(bmp, 10, 44, i*10, 255, 0, 0);
		draw_vline_BMP(bmp, i*10, 10, 44, 0, 0, 255);
		draw_hline_BMP(bmp, 0, 10, i*42, 255, 0, 0);
		draw_vline_BMP(bmp, i*42, 0, 10, 0, 0, 255);
	}
	write_BMP(bmp, 0);
	display_info_BMP(bmp);
	destroy_BMP(bmp);
	return 0;
}
