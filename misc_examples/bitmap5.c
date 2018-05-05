#include "../common/bitmap.h"
#include <time.h>

int main(void)
{
	BITMAP_FILE *bmp;

	srand(time(NULL));
	if (create_BMP("test.bmp", 64, 64, 24)) {
		fprintf(stderr, "Error creating bitmap.\n");
		return 2;
	}

	bmp = load_BMP("test.bmp");
	if (!bmp) {
		fprintf(stderr, "Error loading bitmap.\n");
		return 2;
	}
	make_BMP(bmp);
	destroy_BMP(bmp);
	return 0;
}
