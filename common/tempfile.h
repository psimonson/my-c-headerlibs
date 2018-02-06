/************************************************
 * tempfile.h - Helper Functions (Common Tasks) *
 ************************************************
 * Created by Philip R. Simonson (aka 5n4k3)    *
 ************************************************
 */

#ifndef TEMPFILE_H
#define TEMPFILE_H

#include <stdio.h>
#include <errno.h>

/* ---------------- File Functions ----------------- */

#define TMPFILE_NAME "file.tmp"

static FILE *__tmp_file = NULL;

static void exit_func(void)
{
	if (__tmp_file != NULL) {
		fclose(__tmp_file);
		remove(TMPFILE_NAME);
		__tmp_file = NULL;
	}
}

static FILE *tempfile(void)
{
	FILE *fp = fopen(TMPFILE_NAME, "w+b");
	__tmp_file = fp;
	atexit(&exit_func);
	return fp;
}

#endif

