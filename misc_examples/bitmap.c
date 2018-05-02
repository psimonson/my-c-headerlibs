#include "../common/bitmap.h"

/* program to test load bmp file */
int main(int argc, char *argv[])
{
	BITMAP_FILE *bmp;

	bmp = load_BMP("test.bmp");
	if (!bmp)
		return 1;
	display_info_BMP(bmp);
	destroy_BMP(bmp);

	return 0;
}
