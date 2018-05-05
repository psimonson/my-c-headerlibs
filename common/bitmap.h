/****************************************************************
 * bitmap.h - Header library for loading bitmaps and converting *
 * them to ascii. Also, will do other stuff with bitmaps in the *
 * future.                                                      *
 ****************************************************************
 * Created by Philip '5n4k3' Simonson            (05-03-2018)   *
 ****************************************************************
 */

#ifndef PRS_BITMAP_H
#define PRS_BITMAP_H

#define MAX_SHADES 10

#include <stdio.h>
#include <stdlib.h>

typedef struct BITMAP_FILE_HEADER {
	unsigned short header;
	unsigned int size;
	unsigned short res1;
	unsigned short res2;
	unsigned int offset;
	unsigned int info_size;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bpp;
	unsigned int compression;
	unsigned int image_size;
	unsigned int h_res;
	unsigned int v_res;
	unsigned int num_cols;
	unsigned int num_imp;
} BITMAP_FILE_HEADER;

typedef struct BITMAP_FILE {
	BITMAP_FILE_HEADER info;
	unsigned char *data;
} BITMAP_FILE;

/* destroy_BMP:  frees bitmap resources */
static void destroy_BMP(BITMAP_FILE *bmp)
{
	if (bmp) {
		if (bmp->data)
			free(bmp->data);
		free(bmp);
	}
}

/* load_BMP:  loads an image file into a bitmap data structure */
static BITMAP_FILE *load_BMP(const char *filename)
{
	BITMAP_FILE *bmp;
	FILE *fp;

	if ((fp = fopen(filename, "rb")) == NULL) {
		fprintf(stderr, "Error opening BMP file.\n");
		return NULL;
	}
	bmp = (BITMAP_FILE*)malloc(sizeof(BITMAP_FILE));
	if (bmp) {
		/* BMP HEADER */
		fread(&bmp->info.header, 2, 1, fp);
		fread(&bmp->info.size, 4, 1, fp);
		fread(&bmp->info.res1, 2, 1, fp);
		fread(&bmp->info.res2, 2, 1, fp);
		fread(&bmp->info.offset, 4, 1, fp);

		/* BMP HEADER INFO */
		fread(&bmp->info.info_size, 4, 1, fp);
		fread(&bmp->info.width, 4, 1, fp);
		fread(&bmp->info.height, 4, 1, fp);
		fread(&bmp->info.planes, 2, 1, fp);
		fread(&bmp->info.bpp, 2, 1, fp);
		fread(&bmp->info.compression, 4, 1, fp);
		fread(&bmp->info.image_size, 4, 1, fp);
		fread(&bmp->info.h_res, 4, 1, fp);
		fread(&bmp->info.v_res, 4, 1, fp);
		fread(&bmp->info.num_cols, 4, 1, fp);
		fread(&bmp->info.num_imp, 4, 1, fp);

		if (bmp->info.header == 0x4D42) {
			fseek(fp, bmp->info.offset, SEEK_SET);
			bmp->data = malloc(sizeof(unsigned char)*
					bmp->info.size);
			if (bmp->data) {
				fread(bmp->data, 1, bmp->info.size, fp);
				printf("Valid image loaded.\n");
				fclose(fp);
				return bmp;
			} else {
				printf("Cannot alloc for image data.\n");
				fclose(fp);
			}
		} else {
			printf("Image is invalid.\n");
			fclose(fp);
		}
	}
	destroy_BMP(bmp);
	return NULL;
}

/* display_info_BMP:  display info about the bitmap file */
static void display_info_BMP(BITMAP_FILE *bmp)
{
	if (bmp) {
		printf("***INFO BELOW ***\n"
			"***********************************\n"
			"BITMAP HEADER            : %u\n"
			"BITMAP SIZE              : %u\n"
			"BITMAP OFFSET            : %u\n"
			"BITMAP WIDTH             : %u\n"
			"BITMAP HEIGHT            : %u\n"
			"BITMAP BITS PER PIXEL    : %u\n"
			"***********************************\n",
			bmp->info.header, bmp->info.size,
			bmp->info.offset, bmp->info.width,
			bmp->info.height, bmp->info.bpp);
/*		printf("*** Data Below ***\n"
			"***********************************\n"
			"%s\n"
			"***********************************\n",
			bmp->data); */
	}
}

/* BMP_to_asciiart:  convert image data to ascii and print */
#ifdef BMP_PUT_TO_FILE
static void BMP_to_asciiart(BITMAP_FILE *bmp, const char *filename)
#else
static void BMP_to_asciiart(BITMAP_FILE *bmp)
#endif
{
#ifdef BMP_PUT_TO_FILE
	FILE *fp;
#endif
	char shades[MAX_SHADES] = {'#','$','O','=','+','|','-','^','.',' '};
	int average_color;
	int rowsize;
	int x, y;

	if (!bmp)
		return;

#ifdef BMP_PUT_TO_FILE
	if (filename == NULL)
		fp = stdin;
	else {
		if ((fp = fopen(filename, "wb")) == NULL) {
			fprintf(stderr, "Failed to open %s for writing.\n"
					"Cannot write ascii art into it.\n",
					filename);
			destroy_BMP(bmp);
			exit(1);
		}
	}
#endif

	/* get proper row size */
	rowsize = bmp->info.width*3;

	/* loop through converting average color to ascii */
	for (y = bmp->info.height-1; y >= 0; y-=2) {
		for (x = 0; x < rowsize; x+=3) {
			average_color = (bmp->data[x+y*rowsize] +
					bmp->data[x+1+y*rowsize] +
					bmp->data[x+2+y*rowsize]) / 3;

			/* convert to a shade */
			average_color /= (256/MAX_SHADES);
			if (average_color >= MAX_SHADES)
				average_color = MAX_SHADES-1;

			/* write char to stdout */
#ifdef BMP_PUT_TO_FILE
			fputc(shades[average_color], fp);
#else
			putchar(shades[average_color]);
#endif
		}
#ifdef BMP_PUT_TO_FILE
		fputc('\n', fp);
#else
		putchar('\n');
#endif
	}
#ifdef BMP_PUT_TO_FILE
	if (filename != NULL)
		fclose(fp);
#endif
}

/* BMP_to_count:  counts the amount of shades in the whole image */
static void BMP_to_count(BITMAP_FILE *bmp)
{
	char shades[MAX_SHADES] = {'#','$','O','=','+','|','-','^','.',' '};
	int shade_count[MAX_SHADES] = { 0 };
	int average_color;
	int rowsize;
	int x, y;

	if (!bmp)
		return;

	/* get row size */
	rowsize = bmp->info.width*3; /* width * 3 */

	/* loop through converting average color to shade */
	for (y = bmp->info.height-1; y >= 0; y -= 2) {
		for (x = 0; x < rowsize; x += 3) {
			average_color = (bmp->data[x+y*rowsize] +
					bmp->data[x+1+y*rowsize] +
					bmp->data[x+2+y*rowsize]) / 3;

			/* convert to a shade */
			average_color /= (256/MAX_SHADES);
			if (average_color >= MAX_SHADES)
				average_color = MAX_SHADES-1;

			shade_count[average_color]++;
/*			putchar(shades[average_color]); */
		}
/*		putchar('\n'); */
	}
	for (x = 0; x < 10; x++)
		printf("%c: %d\n", shades[x], shade_count[x]);
}

#endif
