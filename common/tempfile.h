/************************************************
 * tempfile.h - Helper Functions (Common Tasks) *
 ************************************************
 * Created by Philip R. Simonson (aka 5n4k3)    *
 ************************************************
 */

#ifndef PRS_TEMPFILE_H
#define PRS_TEMPFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

/* ---------------- Temp File Vars ----------------- */


static FILE *__tempfile = NULL;
static char *__tempfile_name = NULL;

static const char UPPER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char LOWER[] = "abcdefghijklmnopqrstuvwxyz";
static const char NUMBER[] = "0123456789";


/* ---------------- File Functions ----------------- */


static char *generate_tempname(void)
{
	char *name;
	int i, j, k;
	srand(time(NULL));
	name = malloc(18);
	if (name == NULL)
		return NULL;
	for (i = j = 0; i < 8; i++) {
		k = rand() % 3;
		switch (k) {
			case 0:
				j = rand() % 26;
				name[i] = UPPER[j];
			break;
			case 1:
				j = rand() % 26;
				name[i] = LOWER[j];
			break;
			case 2:
				j = rand() % 10;
				name[i] = NUMBER[j];
			break;
			default:
			break;
		}
	}
	name[i++] = '.';
	name[i++] = 't';
	name[i++] = 'm';
	name[i++] = 'p';
	name[i] = '\0';
	return name;
}

static void _tempfile_exit(void)
{
	if (__tempfile != NULL) {
		fclose(__tempfile);
		__tempfile = NULL;
	}
}

static FILE *tempfile(void)
{
	FILE *fp;
	__tempfile_name = generate_tempname();
	fp = fopen(__tempfile_name, "a+b");
	__tempfile = fp;
	atexit(&_tempfile_exit);
	return fp;
}
#endif
