/******************************************************************
 * helper.h - Some helper functions, include this to have a lot   *
 * of functions at your disposel. Some are re-incarnated standard *
 * library functions, some are of my own making.                  *
 ******************************************************************
 * Created by Philip R. Simonson           (05-01-2018)           *
 ******************************************************************
 */

#ifndef PRS_HELPER_H
#define PRS_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#define SWAP(t,x,y) do { t temp = y; x = y; y = temp; } while(0)


/* --------------------------- Boolean Declaration ------------------------ */


typedef enum Boolean {
	FALSE,
	TRUE
} bool_t;

#define true TRUE
#define false FALSE


/* ----------------------------- Stdio Functions -------------------------- */


/* reverse:  reverse s in place */
static void reverse(char *s)
{
	char *p = s;

	while (*p != 0)
		p++;
	while ((p-s) != 0) {
		char tmp = *--p;
		*p = *s;
		*s++ = tmp;
	}
}

/* p_itoa:  convert n to string; store in s */
static void p_itoa(int n, char *s)
{
	char *p = s;
	int sign;

	sign = (n < 0) ? -1 : 1;
	if (n < 0)
		n = -n;
	do {
		*p++ = sign * (n % 10) + '0';
	} while ((n /= 10) > 0);
	*p = '\0';
	reverse(s);
}

/* p_atoi:  convert s to integer; return it */
static int p_atoi(char *s)
{
	int n, sign;

	while (isspace(*s)) s++;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		s++;
	for (n = 0; isdigit(*s); s++)
		n = 10 * n + (*s - '0');
	return n*sign;
}


/* ---------------------------- Memory Functions -------------------------- */


/* p_zero:  zero memory; n amount in p */
static void p_zero(void *p, size_t n)
{
	char *s = (char*)p;

	while (s < (char*)p+n) *s++ = 0;
}

/* mem_set:  sets p to c amount of n */
static void *mem_set(void *p, int c, size_t n)
{
	char *s = (char*)p;

	while (s < (char*)p+n)
		*(char*)s++ = c;
	return p;
}

/* mem_cpy:  copies t to s; n amount of bytes */
static void mem_cpy(void *s, void *t, size_t n)
{
	char *t2 = (char*)t;

	while (t2 < (char*)t+n)
		*(char*)s++ = *(char*)t2++;
}

/* mem_cmp:  compare t to s; n amount of bytes */
static int mem_cmp(void *s, void *t, size_t n)
{
	char *t2 = (char*)t;

	while (t2 < (char*)t+n)
		if (*t2++ != *(char*)s++)
			return (*(char*)s-*t2);
	return 0;
}


/* ---------------------------- String Functions -------------------------- */


/* trim:  trim off newlines from string */
static int trim(char *s)
{
	char *p = s;

	while (*p++ != 0);
	while (*--p != '\r' || *p != '\n');
	return p-s;
}

/* str_len:  get length of a null terminated string */
static int str_len(const char *s)
{
	const char *p = s;
	while (*p != '\0')
		p++;
	return p-s;
}

/* str_cat:  concatenate t on end of s; assume s is big enough */
static int str_cat(char *s, const char *t)
{
	const char *t2 = t;
	char *s2 = s;

	while (*s2 != '\0')
		s2++;
	while ((*s2++ = *t2++) != 0);
	return (s2-s)-1;
}

/* str_cpy:  copy t to s; assume s is big enough */
static int str_cpy(char *s, const char *t)
{
	const char *t2 = t;
	char *s2 = s;

	while ((*s2++ = *t2++) != 0);
	return (s2-s)-1;
}

/* str_cmp:  compares t to s; null terminated strings */
static int str_cmp(const char *s, const char *t)
{
	while (*s == *t++)
		if (*s++ == '\0')
			return 0;
	return (*s-*t);
}

/* strn_cat:  concatenates n amount of chars from t to s */
static int strn_cat(char *s, const char *t, size_t n)
{
	const char *t2 = t;
	char *s2 = s;

	while (*s2 != '\0')
		s2++;
	while (t2 < t+n)
		*s2++ = *t2++;
	*s2 = 0;
	return (s2-s)-1;
}

/* strn_cpy:  copies n amount of chars from t to s */
static int strn_cpy(char *s, const char *t, size_t n)
{
	const char *t2 = t;
	char *s2 = s;

	while (t2 < t+n)
		*s++ = *t2++;
	return (s-s2);
}

/* strn_cmp:  compares t to s; n amount of chars */
static int strn_cmp(char *s, const char *t, size_t n)
{
	char *s2 = s;

	while (s2 < s+n)
		if (*s2++ != 0)
			return (s2-t);
	return 0;
}

/* str_dup:  duplicates s; returns pointer of dupped string */
static char *str_dup(const char *s)
{
	char *p;

	/* allocate memory for s */
	p = (char*)malloc(str_len(s)+1);
	if (p == 0)
		return NULL;

	/* copy string into p */
	while ((*p++ = *s++));
	return p;
}


/* ----------------------- Miscellaneous Functions ----------------------- */


/* getstr:  gets a string from standard input */
static int getstr(char *s, int lim)
{
	char *p;

	for (p = s; --lim > 0 && (*p = getchar()) != EOF && *p != '\n'; p++);
	*p = '\0';
	return p-s;
}

/* get_input:  gets input with getstr; displays message first */
static int get_input(const char *msg, char *s, int lim)
{
	printf("%s", msg);
	return getstr(s, lim);
}


#endif
