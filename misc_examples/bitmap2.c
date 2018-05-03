#include "../common/bitmap.h"

/* program to test load bmp file */
int main(int argc, char *argv[])
{
	BITMAP_FILE *bmp;

	bmp = load_BMP("test.bmp");
	if (!bmp)
		return 1;
	BMP_to_asciiart(bmp);
	destroy_BMP(bmp);

	return 0;
}
