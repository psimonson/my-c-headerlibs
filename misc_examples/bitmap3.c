#define BMP_PUT_TO_FILE
#include "../common/bitmap.h"

int main(int argc, char **argv)
{
	BITMAP_FILE *bmp;

	if (argc > 3) {
		fprintf(stderr, "Usage: %s [bmpfile]\n", argv[0]);
		return 1;
	}

	/* Load a bitmap named test.bmp */
	if (argc == 2 || argc == 3)
		bmp = load_BMP(argv[1]);
	else
		bmp = load_BMP("test.bmp");
	if (!bmp)		/* check for loading error */
		return 1;

	if (argc == 3) {
		BMP_to_asciiart(bmp, argv[2]);
	} else {
		BMP_to_asciiart(bmp, NULL);
	}
	BMP_to_count(bmp);	/* count shades in bitmap */
	destroy_BMP(bmp);	/* free bmp resources */
	return 0;		/* return success */
}
