#include "../common/bitmap.h"

/* clear_BMP:  clear bitmap data to solid color */
void clear_BMP(BITMAP_FILE *bmp, unsigned char color)
{
	int rowsize;
	int x,y;

	if (bmp) {
		rowsize = bmp->header.info.width*3;
		for (y=bmp->header.info.height-1; y >= 0; y--) {
			for (x=0; x < bmp->header.info.width*3; x++) {
				bmp->data[x+y*rowsize] = color;
			}
		}
	}
}

/* put_pixel_BMP:  plot a pixel at given x and y with given r/g/b values */
void put_pixel_BMP(BITMAP_FILE *bmp, int x, int y,
		unsigned char color)
{
	int rowsize;

	if (bmp) {
		rowsize = bmp->header.info.width*3;
		bmp->data[x+y*rowsize] = color;
	}
}

/* draw_line_BMP:  draw a line from x1,y1 to x2,y2 with r/g/b color */
void draw_line_BMP(BITMAP_FILE *bmp, int x1, int x2, int y,
		unsigned char color)
{
	if (bmp) {
		for (x1=0; x1 <= x2; x1++)
			put_pixel_BMP(bmp, x1, y, color);
	}
}

int main(void)
{
	BITMAP_FILE *bmp;

	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;
	clear_BMP(bmp, 0x00);
	draw_line_BMP(bmp, 32, 40, 50, 0xff);
	write_BMP(bmp, 0);
	destroy_BMP(bmp);
	return 0;
}
