#include "../common/bitmap.h"

/* program to test load bmp file */
int main(int argc, char *argv[])
{
	BITMAP_FILE *bmp;

	if (argc > 2) {
		fprintf(stderr, "Usage: %s [bmpfile]\n", argv[0]);
		return 1;
	}

	if (argc == 2)
		bmp = load_BMP(argv[1]);
	else
		bmp = load_BMP("test.bmp");
	if (check_BMP(bmp))
		return 1;
	BMP_to_asciiart(bmp);
	destroy_BMP(bmp);

	return 0;
}
