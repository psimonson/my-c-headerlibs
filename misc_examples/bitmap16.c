/*
 * Program: bitmap.c
 * Author : Philip R. Simonson
 * Desc.  : Simple bitmap to gray scale.
 */

#define BMP_PUT_TO_FILE
#include "../common/bitmap.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	BITMAP_FILE *bmp;
	bmp = load_BMP("test.bmp");
	if (check_BMP(bmp) != BITMAP_NO_ERROR)
		return 1;
	
	BMP_to_asciiart(bmp, "test.txt");
	destroy_BMP(bmp);
	return 0;
}
