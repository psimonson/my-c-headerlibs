#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;

	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (check_BMP(bmp))
		return 1;
	clear_BMP(bmp, 0, 0, 0);

	/* draw blue head */
	draw_hcircle_BMP(bmp, 10, 10, 10, 0, 0, 255);

	/* draw body */
	draw_line_BMP(bmp, 12, 12, 12, 45, 0, 0, 255);
	draw_line_BMP(bmp, 0, 0, 12, 12, 0, 0, 255);
	draw_line_BMP(bmp, 12, 12, 22, 0, 0, 0, 255);
	draw_line_BMP(bmp, 0, 22, 12, 32, 0, 0, 255);
	draw_line_BMP(bmp, 12, 32, 22, 22, 0, 0, 255);

	write_BMP(bmp, 0);
	if (check_BMP(bmp))
		return 1;
	destroy_BMP(bmp);
	return 0;
}
