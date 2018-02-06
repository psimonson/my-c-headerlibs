/********************************************
 * prs_string.h - Simple String Functions
 * Created by Philip "5n4k3" Simonson
 ********************************************
 */

#ifndef PRS_STRING_H
#define PRS_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAXLINE 512

static int readln(char s[], int limit)
{
	char c;
	int remain;
	int i;
	i = 0;
	remain = 1;
	while (remain) {
		c = getchar();
		if (c == '\n' || c == EOF) {
			remain = 0;
		} else if (i < limit) {
			if (c == '\b') {
				s[i] = 0;
				--i;
			} else {
				s[i] = c;
				++i;
			}
		}
	}
	s[i] = '\0';
	return i;
}

static int readln2(char s[], int limit)
{
	char c;
	int remain;
	int i;
	i = 0;
	remain = 1;
	while (remain) {
		c = getchar();
		if (c == '\n' || c == EOF) {
			s[i++] = c;
			remain = 0;
		} else if (i < limit) {
			if (c == '\b') {
				s[i] = 0;
				--i;
			} else {
				s[i] = c;
				++i;
			}
		}
	}
	s[i] = '\0';
	return i;
}

static int str_length(const char s[])
{
	int i;
	for (i = 0; s[i] != 0; i++);
	return i;
}

static int str_copy(char s1[], char s2[])
{
	int i;
	for (i = 0; (s1[i] = s2[i]) != 0; i++);
	s1[i] = '\0';
	return i;
}

static int str_cmp(char s1[], char s2[])
{
	int retval;
	int i;

	i = retval = 0;
	while (s2[i] != '\0' && !retval) {
		retval = (s1[i] - s2[i]);
		++i;
	}
	return retval;
}

static int trim_string(char s[])
{
	int i;
	for (i = str_length(s)-1; i >= 0; i--)
		if (s[i] == '\n' || s[i] == '\r')
			s[i] = '\0';
	return i;
}

static char* str_dup(char s[])
{
	char* retstr;
	int size;
	size = str_length(s)+1;
	retstr = malloc(size);
	if (!retstr)
		return NULL;
	str_copy(retstr, s);
	return retstr;
}

#endif
