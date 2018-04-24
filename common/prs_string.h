/********************************************
 * prs_string.h - Simple String Functions
 * Created by Philip "5n4k3" Simonson
 ********************************************
 */

#define PRS_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* readln:  get user input from keyboard */
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
		} else if (i < limit-1) {
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

/* readln2:  gets user input from keyboard; with newline */
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
			s[i++] = '\n';
			remain = 0;
		} else if (i < limit-2) {
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

/* get_input:  like readln except prompts user with message */
static int get_input(const char message[], char s[], int lim)
{
	int bytes;
	printf("%s", message);
	bytes = readln(s, lim);
	return bytes;
}

/* str_length:  returns length of string */
static int str_length(const char s[])
{
	int i;
	for (i = 0; s[i] != 0; i++);
	return i;
}

/* str_copy:  copies one string to another */
static int str_copy(char s1[], const char s2[])
{
	int i;
	for (i = 0; (s1[i] = s2[i]) != 0; i++);
	s1[i] = '\0';
	return i;
}

/* str_cmp:  compares two strings; returns 0 if perfect match */
static int str_cmp(const char s1[], const char s2[])
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

/* trim_string:  trims off carrage return and line feed chars */
static int trim_string(char s[])
{
	int i;
	for (i = str_length(s)-1; i >= 0; i--)
		if (s[i] == '\n' || s[i] == '\r')
			s[i] = '\0';
	return i;
}

/* str_dup:  duplicate a string; store into heap */
static char* str_dup(const char s[])
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
