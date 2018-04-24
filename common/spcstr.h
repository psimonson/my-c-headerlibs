/*****************************************************************
 * spcstr.h - Special String Header Library
 *
 * Description: This string library creates a dynamic string or a
 * dynamic string holder.
 *
 * Created by Philip "5n4k3" Simonson.
 *****************************************************************
 */

#define PRS_SPCSTR_H

#ifndef PRS_STRING_H
#include "prs_string.h"
#endif

#define DYN_START_SIZE 16

/* global dynamic array variable */
static int __dyn_array_count;
static char **__dyn_array;

/* dyn_free:  frees all allocated memory for dyn_array */
static void dyn_free(void)
{
	int i;
	if (__dyn_array == NULL)
		return;
	i = 0;
	while (__dyn_array[i] != NULL) {
		free(__dyn_array[i++]);
	}
	free(__dyn_array);
}

/* dyn_init:  initializes the dynamic array pointer */
static int dyn_init(void)
{
	int i;
	if (__dyn_array != NULL) {
		__dyn_array_count += DYN_START_SIZE;
		__dyn_array = (char**)realloc(__dyn_array, __dyn_array_count*sizeof(char*));
		if (__dyn_array == NULL)
			return -1;
	} else {
		__dyn_array = (char**)malloc(sizeof(char*)*DYN_START_SIZE);
		if (__dyn_array == NULL)
			return -1;
		__dyn_array_count = DYN_START_SIZE;
		while (i < __dyn_array_count+1)
			__dyn_array[i++] = NULL;
	}
	return 0;
}

/* dyn_string:  creates a dynamic string for dynamic string array */
static int dyn_string(const char *string)
{
	static int count = 0;
	char *s;
	s = str_dup(string);
	if (s == NULL)
		return -1;
	if (count < __dyn_array_count)
		__dyn_array[count++] = s;
	return 0;
}

/* dyn_display:  displays the entire list of strings stored */
static void dyn_display(void)
{
	int count = 0;
	while (__dyn_array[count] != NULL && count < __dyn_array_count)
		printf("%s", __dyn_array[count++]);
}

