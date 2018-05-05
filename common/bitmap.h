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

#ifndef PRS_HELPER_H
#include "helper.h"
#endif
#include <stdlib.h>

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#pragma pack(push, 1)
typedef struct BITMAP_FILE_HEADER {
	unsigned short header;
	unsigned int size;
	unsigned short res1;
	unsigned short res2;
	unsigned int offset;
} BITMAP_HEADER;

typedef struct BITMAP_INFO_HEADER {
	unsigned int size;
	unsigned int width;
	unsigned int height;
	unsigned short col_planes;
	unsigned short bpp;
	unsigned int compression;
	unsigned int image_size;
	unsigned int h_res;
	unsigned int v_res;
	unsigned int num_cols;
	unsigned int num_imp;
} BITMAP_INFO;

typedef struct BITMAP {
	BITMAP_HEADER file;
	BITMAP_INFO info;
} BITMAP;
#pragma pack(pop)

typedef struct BITMAP_FILE {
	BITMAP header;
	char fname[MAX_PATH];
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
		/* set bitmap name */
		str_cpy(bmp->fname, filename);

		/* BMP HEADER */
		fread(&bmp->header.file.header, 2, 1, fp);
		fread(&bmp->header.file.size, 4, 1, fp);
		fread(&bmp->header.file.res1, 2, 1, fp);
		fread(&bmp->header.file.res2, 2, 1, fp);
		fread(&bmp->header.file.offset, 4, 1, fp);

		/* BMP HEADER INFO */
		fread(&bmp->header.info.size, 4, 1, fp);
		fread(&bmp->header.info.width, 4, 1, fp);
		fread(&bmp->header.info.height, 4, 1, fp);
		fread(&bmp->header.info.col_planes, 2, 1, fp);
		fread(&bmp->header.info.bpp, 2, 1, fp);
		fread(&bmp->header.info.compression, 4, 1, fp);
		fread(&bmp->header.info.image_size, 4, 1, fp);
		fread(&bmp->header.info.h_res, 4, 1, fp);
		fread(&bmp->header.info.v_res, 4, 1, fp);
		fread(&bmp->header.info.num_cols, 4, 1, fp);
		fread(&bmp->header.info.num_imp, 4, 1, fp);

		if (bmp->header.file.header == 0x4D42) {
			fseek(fp, bmp->header.file.offset, SEEK_SET);
			bmp->data = malloc(sizeof(unsigned char)*
					bmp->header.info.image_size);
			if (bmp->data) {
				fread(bmp->data, 1,
					bmp->header.info.image_size, fp);
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
			bmp->header.file.header, bmp->header.file.size,
			bmp->header.file.offset, bmp->header.info.width,
			bmp->header.info.height, bmp->header.info.bpp);
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
	rowsize = bmp->header.info.width*3;

	/* loop through converting average color to ascii */
	for (y = bmp->header.info.height-1; y >= 0; y -= 2) {
		for (x = 0; x < rowsize; x += 3) {
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
	rowsize = bmp->header.info.width*3; /* width * 3 */

	/* loop through converting average color to shade */
	for (y = bmp->header.info.height-1; y >= 0; y -= 2) {
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

/* create_BMP:  make a blank BMP file; from given width/height/bitsperpixel */
static int create_BMP(const char *filename, unsigned int w, unsigned int h,
	unsigned short bpp)
{
	BITMAP_FILE *bmp;
	FILE *fp;
	const int pixel_byte_size = h*w*bpp/8;
	const int file_size = sizeof(BITMAP)+pixel_byte_size;

	if ((fp = fopen(filename, "wb")) == NULL) {
		fprintf(stderr, "Error open file for writing.\n");
		return 1;
	}
	bmp = (BITMAP_FILE*)calloc(1, sizeof(BITMAP_FILE));
	if (!bmp) {
		fclose(fp);
		return 2;
	}
	bmp->data = (unsigned char*)malloc(pixel_byte_size);
	if (!bmp->data) {
		destroy_BMP(bmp);
		fclose(fp);
		return 2;
	}

	mem_set(bmp->fname, 0, sizeof bmp->fname);

	/* setup bitmap file header */
	bmp->header.file.header = 0x4D42;
	bmp->header.file.size = file_size;
	bmp->header.file.res1 = 0;
	bmp->header.file.res2 = 0;
	bmp->header.file.offset = sizeof(BITMAP);

	/* setup bitmap info header */
	bmp->header.info.size = sizeof(BITMAP_INFO);
	bmp->header.info.width = w;
	bmp->header.info.height = h;
	bmp->header.info.col_planes = 1;
	bmp->header.info.bpp = bpp;
	bmp->header.info.compression = 0;
	bmp->header.info.image_size = pixel_byte_size;
	bmp->header.info.h_res = 0x130B;
	bmp->header.info.v_res = 0x130B;
	bmp->header.info.num_cols = 0;
	bmp->header.info.num_imp = 0;

	/* wipe pixel data */
	fwrite(&bmp->header, 1, sizeof(BITMAP), fp);
	mem_set(bmp->data, 0xFF, pixel_byte_size);
	fwrite(bmp->data, 1, pixel_byte_size, fp);
	fclose(fp);

	destroy_BMP(bmp);
	return 0;
}

/* make_BMP:  set data; overwriting file */
static void make_BMP(BITMAP_FILE *bmp)
{
	FILE *fp;
	int rowsize;
	int x,y;

	if ((fp = fopen(bmp->fname, "r+b")) == NULL) {
		fprintf(stderr, "Cannot open file for writing.\n");
		return;
	}
	fseek(fp, bmp->header.file.offset, SEEK_SET);
	if (bmp->data) {
		mem_set(bmp->data, 0xff, bmp->header.info.image_size);
		rowsize = bmp->header.info.width*3;
		for (y=bmp->header.info.height-1; y >= 0; y--) {
			for (x=0; x < rowsize; x++) {
				bmp->data[x+y*rowsize] = rand()%255;
				bmp->data[x+1+y*rowsize] = rand()%255;
				bmp->data[x+2+y*rowsize] = rand()%255;
			}
		}
		fwrite(bmp->data, 1, bmp->header.info.image_size, fp);
	}
	fclose(fp);
}

#endif
