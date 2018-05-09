/*****************************************************************
 * spcstr.h - Special String Header Library
 *
 * Description: This string library creates a dynamic string or a
 * dynamic string holder.
 *
 * Created by Philip "5n4k3" Simonson.
 *****************************************************************
 */

#ifndef PRS_SPCSTR_H
#define PRS_SPCSTR_H

#ifndef PRS_STRING_H
#include "helper.h"
#endif

#define DYN_START_SIZE 8

/* global dynamic array variable */
static int __dyn_array_count;
static char **__dyn_array;

/* dyn_free:  frees all allocated memory for dyn_array */
static void dyn_free(void)
{
	int i;

	for (i=0; i < __dyn_array_count; i++)
		free(__dyn_array[i]);
	free(__dyn_array);
	__dyn_array = NULL;
}

/* dyn_init:  initializes the dynamic array pointer */
static int dyn_init(void)
{
	int i;

	__dyn_array = (char**)malloc(sizeof(char*)*DYN_START_SIZE);
	if (__dyn_array == NULL)
		return -1;
	__dyn_array_count = DYN_START_SIZE;
	i = 0;
	while (i < __dyn_array_count)
		__dyn_array[i++] = NULL;
	return 0;
}

/* __dyn_grow:  grows the char** array; do NOT use manually */
static int __dyn_grow(void)
{
	char **p;
	int i;

	if (!__dyn_array)
		return -1;

	__dyn_array_count += DYN_START_SIZE;
	p = (char**)calloc(1, sizeof(char*)*__dyn_array_count);
	if (!p) {
		__dyn_array_count -= DYN_START_SIZE;
		return -1;
	}
	for (i=0; i < __dyn_array_count-DYN_START_SIZE; i++) {
		p[i] = __dyn_array[i];
	}
	free(__dyn_array);
	__dyn_array = p;
	return 0;
}

/* dyn_string:  creates a dynamic string for dynamic string array */
static int dyn_string(const char *string)
{
	static int i = 0;
	char *s;

	s = str_dup(string);
	if (s == NULL)
		return -1;

	if (i >= __dyn_array_count)
		__dyn_grow();

	while (i < __dyn_array_count) {
		if (__dyn_array[i] == NULL)
			break;
		++i;
	}
	__dyn_array[i] = s;
	return 0;
}

/* dyn_display:  displays the entire list of strings stored */
static void dyn_display(void)
{
	int count = 0;
	while (count < __dyn_array_count) {
		if (__dyn_array[count] != NULL)
			printf("%s", __dyn_array[count]);
		count++;
	}
}

#endif
