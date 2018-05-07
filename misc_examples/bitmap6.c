#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;
	int rowsize;
	int x,y,i;

	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp) {
		printf("Error creating bitmap.\n");
		return 1;
	}
	rowsize = bmp->header.info.width*3;
	for (y=bmp->header.info.height-1; y >= 0; y--) {
		for (x=0; x < rowsize; x++) {
			for (i=0; i < 3; i++)
				bmp->data[x+i+(y*rowsize)] = rand()%255;
		}
	}
	write_BMP(bmp, 0);
	destroy_BMP(bmp);
	return 0;
}
