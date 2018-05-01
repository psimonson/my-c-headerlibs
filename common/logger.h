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

#ifndef PRS_LOGGER_H
#define PRS_LOGGER_H

#ifndef PRS_TEMPFILE_H
#include "tempfile.h"
#endif
#ifndef PRS_HELPER_H
#include "helper.h"
#endif

#include <stdlib.h>
#include <stdarg.h>
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
		free(__logname);
		__logname = NULL;
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

	mem_set(buf, 0, sizeof buf);
	while (fgets(buf, sizeof(buf)-1, __logfile) != NULL) {
		fputs(buf, stdout);
		mem_set(buf, 0, sizeof buf);
	}
	close_log();
	return 0;
}

static char *__cryptname = NULL;  /* store name for re-write of file */

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
		c ^= key[i%str_len(key)] & 0xf0;
		fputc(c, tmp);
		i++;
	}
	close_log();
	rewind(tmp);
	if (open_log(__cryptname, "wb") < 0)
		exit(EXIT_FAILURE);
	total = 0;
	while ((bytes = fread(buf, 1, sizeof(buf), tmp)) > 0) {
		bytes_wrote = fwrite(buf+total, 1, bytes, __logfile);
		total += bytes_wrote;
	}
	fclose(tmp);
	close_log();
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
	else
		__logname = generate_tempname();
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
	free(__cryptname);
	return 0;
}

static int do_log2(int (*func)(void),
		const char *log_name)
{
	if (func == NULL)
		return -1;
	if (log_name != NULL)
		__logname = str_dup(log_name);
	else
		__logname = generate_tempname();
	if (func == &crypt_log) {
		if (open_log(__logname, "rb") < 0)
			return -1;
		__cryptname = str_dup(__logname);
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
