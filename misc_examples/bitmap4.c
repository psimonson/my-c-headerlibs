#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;

	bmp = create_BMP("hello_1337.bmp", 800, 600, 24);
	if (check_BMP(bmp))
		return 1;
	make_BMP(bmp);
	write_BMP(bmp, 0);
	if (check_BMP(bmp))
		return 1;
	destroy_BMP(bmp);
	return 0;
}
