/***********************************************
 * logger.h - Logging Header Library
 ***********************************************
 * Use this in a program to keep a log file of
 * whatever you need to. This will automatically
 * write to a file of a desired name.
 ***********************************************
 * Create by Philip "5n4k3" Simonson
 ***********************************************
 */

#ifndef LOGGER_H
#define LOGGER_H

#include "tempfile.h"
#include "prs_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#define NAMESIZ 256

static char *__logname = NULL;
static FILE *__logfile = NULL;
extern const char key[];


/* -------------- functions below here -------------- */


/* start_log:  initialize the buf and log file */
static int open_log(const char *filename, const char *open_mode)
{
	if (filename == NULL && __logname == NULL) {
		__logfile = tempfile();
		__logname = __tempfile_name;
	} else {
		if ((__logfile = fopen((filename == NULL) ? __logname : filename,
				open_mode)) == NULL) {
			fprintf(stderr, "Error: Cannot open log file.\n");
			return -1;
		}
	}
	return 0;
}

/* close_log:  closes the log file stream */
static void close_log(void)
{
	if (__logfile != NULL) {
		fclose(__logfile);
		__logfile = NULL;
	}
}

/* append_log:  append to the end of log file; string with args */
static int append_log(const char *s, va_list args)
{
	vfprintf(__logfile, s, args);
	close_log();
	return 0;
}

/* write_log:  write out to log file; given string */
static int write_log(const char *s, va_list args)
{
	vfprintf(__logfile, s, args);
	close_log();
	return 0;
}

/* read_log:  reads an entire log file displaying contents in stdout */
static int read_log(void)
{
	char buf[BUFSIZ];

	memset(buf, 0, sizeof buf);
	while (fgets(buf, sizeof(buf)-1, __logfile) != NULL) {
		fputs(buf, stdout);
		memset(buf, 0, sizeof buf);
	}
	return 0;
}

/* crypt_log:  encrypts/decrypts log file */
static int crypt_log(void)
{
	FILE *tmp = NULL;
	char buf[BUFSIZ];
	int bytes, bytes_wrote;
	int total;
	int c, i;

	if ((tmp = tmpfile()) == NULL)
		return -1;
	rewind(__logfile);
	i = 0;
	while ((c = fgetc(__logfile)) != EOF) {
		c ^= key[i%strlen(key)] & 0xf0;
		fputc(c, tmp);
		i++;
	}
	rewind(tmp);
	rewind(__logfile);
	if (open_log(__logname, "wb") < 0)
		return -1;
	total = 0;
	while ((bytes = fread(buf, 1, sizeof(buf), tmp)) > 0) {
		bytes_wrote = fwrite(buf+total, 1, bytes, __logfile);
		total += bytes_wrote;
	}
	fclose(tmp);
	return 0;
}

static int do_log(int (*func)(const char *, va_list args),
		const char *log_name, const char *log_text, ...)
{
	va_list args;
	if (func == NULL)
		return -1;
	if (log_name != NULL)
		__logname = str_dup(log_name);
	if (func == &append_log) {
		if (open_log(__logname, "a+b") < 0)
			return -1;
	} else if (func == &write_log) {
		if (open_log(__logname, "w+b") < 0)
			return -1;
	} else {
		fprintf(stderr, "Error: Unknown operation function.\n");
		return -2;
	}
	va_start(args, log_text);
	if ((*func)(log_text, args) < 0) {
		return -1;
	}
	va_end(args);
	close_log();
	return 0;
}

static int do_log2(int (*func)(void),
		const char *log_name)
{
	if (func == NULL)
		return -1;
	if (log_name != NULL)
		__logname = str_dup(log_name);
	if (func == &crypt_log) {
		if (open_log(__logname, "a+b") < 0)
			return -1;
	} else if (func == &read_log) {
		if (open_log(__logname, "r+b") < 0)
			return -1;
	} else {
		fprintf(stderr, "Error: Unknown operation function.\n");
		return -2;
	}
	if ((*func)() < 0)
		return -1;
	close_log();
	return 0;
}

#endif
