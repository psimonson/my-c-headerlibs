#ifndef _PRS_DEBUG_H_
#define _PRS_DEBUG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

void debug_print(const char *format, ...)
{
	char msg[512];
	va_list ap;
	va_start(ap, format);
	strcpy(msg, "[DEBUG]: ");
	strcat(msg, format);
	strcat(msg, "\n");
	vfprintf(stderr, msg, ap);
	va_end(ap);
}

int error_print(const char *format, ...)
{
	char msg[512];
	va_list ap;
	va_start(ap, format);
	strcpy(msg, "[DEBUG]: ");
	strcat(msg, format);
	strcat(msg, "\n");
	vfprintf(stderr, msg, ap);
	va_end(ap);
	if (!errno)
		return 0;
	return errno;
}

int check_mem(void *mem)
{
#ifndef NDEBUG
	if (mem != NULL)
		debug_print("memory block (%p) okay.", mem);
#endif
	return (mem != NULL);
}

int free_mem(void *mem)
{
	if (mem != NULL) {
		free(mem);
#ifndef NDEBUG
		debug_print("memory block (%p) freed.", mem);
#endif
		mem = NULL;
	}
	return (mem != NULL);
}

#endif
