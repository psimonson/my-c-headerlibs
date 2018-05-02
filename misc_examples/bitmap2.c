#include "../common/bitmap.h"

char ascii[6] = { ' ', '.', ':', '/', '\\', '#' };

/* BMP_to_ascii:  convert image data to ascii and print */
void BMP_to_ascii(BITMAP_FILE *bmp)
{
	int i, j;

	for (i = 0; i < bmp->header.size; i++) {
		for (j = 0; j < 3; j++) {
			if (bmp->data[i*j] > 5 && bmp->data[i*j] <= 50)
				putchar(ascii[1]);
			else if ((bmp->data[i*j] > 50) && (bmp->data[i*j] <= 100))
				putchar(ascii[2]);
			else if ((bmp->data[i*j] > 100) && (bmp->data[i*j] <= 150))
				putchar(ascii[3]);
			else if ((bmp->data[i*j] > 150) && (bmp->data[i*j] <= 250))
				putchar(ascii[4]);
			else if ((bmp->data[i*j] > 250) && (bmp->data[i*j] <= 255))
				putchar(ascii[5]);
			else
				putchar(ascii[0]);
		}
	}
}

/* program to test load bmp file */
int main(int argc, char *argv[])
{
	BITMAP_FILE *bmp;

	bmp = load_BMP("test.bmp");
	if (!bmp)
		return 1;
	BMP_to_ascii(bmp);
	destroy_BMP(bmp);

	return 0;
}
