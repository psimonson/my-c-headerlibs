#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;
	int i;

	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;

	clear_BMP(bmp, 0, 0, 0);
	for (i=1; i < 3; i++) {
		/* draw middle square */
		draw_hline_BMP(bmp, 20, 40, i*20, 0, 0, 255);
		draw_vline_BMP(bmp, (i*20), 20, 40, 255, 0, 0);
		/* draw bottom left square */
		draw_hline_BMP(bmp, 10, 20, i*10, 0, 0, 255);
		draw_vline_BMP(bmp, i*10, 10, 20, 255, 0, 0);
		/* draw upper right square */
		draw_hline_BMP(bmp, 40, 50, bmp->header.info.height-5-(i*10),
				0, 0, 255);
		draw_vline_BMP(bmp, bmp->header.info.width-4-(i*10),
				40, 50, 255, 0, 0);
	}
	write_BMP(bmp, 0);
	display_info_BMP(bmp);
	destroy_BMP(bmp);
	return 0;
}
