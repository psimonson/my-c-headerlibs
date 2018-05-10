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

#define UP 1
#define DOWN 0

#define SWAP(t,x,y) do { t temp = y; x = y; y = temp; } while(0)


/* ---------------------------- Misc Enumerations ------------------------- */


enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t',
		NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };


/* --------------------------- Boolean Declaration ------------------------ */


typedef enum Boolean {
	false,
	true
} bool_t;

#if !defined(TRUE) && !defined(FALSE)
#define TRUE
#define FALSE
#endif


/* ---------------------------- Memory Functions -------------------------- */


/* p_zero:  zero memory; n amount in p */
static void p_zero(void *p, size_t n)
{
	char *s = (char*)p;

	while ((s-(char*)p) < n) *s++ = 0;
}

/* mem_set:  sets p to c amount of n */
static void *mem_set(void *p, int c, size_t n)
{
	char *s = (char*)p;

	while ((s-(char*)p) < n)
		*(char*)s++ = c;
	return p;
}

/* mem_cpy:  copies t to s; n amount of bytes */
static void mem_cpy(void *s, void *t, size_t n)
{
	char *t2 = (char*)t;

	while (t2-((char*)t) < n)
		*(char*)s++ = *(char*)t2++;
}

/* mem_cmp:  compare t to s; n amount of bytes */
static int mem_cmp(void *s, void *t, size_t n)
{
	char *t2 = (char*)t;

	while ((t2-(char*)t) < n)
		if (*t2++ != *(char*)s++)
			return (*(char*)s-*t2);
	return 0;
}


/* ---------------------------- String Functions -------------------------- */


/* str_len:  get length of a null terminated string */
static int str_len(const char *s)
{
	const char *p = s;

	while (*p != 0)
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
	str_cpy(p, s);
	return p;
}

/* trim:  trim off newlines from string */
static int trim(char *s)
{
	char *p;

	for (p=s; *p != '\0'; p++)
		if (*p == '\r' || *p == '\n')
			break;
	*p = 0;
	return (int)(p-s);
}


/* ----------------------------- Stdio Functions -------------------------- */


/* reverse:  reverse s in place */
static void reverse(char *s)
{
	if (s != 0 && *s != '\0') {
		char *p = s+str_len(s)-1;

		while (s < p) {
			char tmp = *s;
			*s++ = *p;
			*p-- = tmp;
		}
	}
}

/* reverse_r:  recursively reverse s in place */
static void reverse_r(char *s)
{
	static char *p = 0;

	if (p == 0) {
		p = s+str_len(s)-1;
	}
	if (p-s > 0) {
		int tmp = *p;
		*p-- = *s;
		*s++ = tmp;
		reverse_r(s);
	} else {
		p = 0;
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

/* itoa_r:  convert n to string; store in s */
static void itoa_r(int n, char *s)
{
	char *p = s;
	int sign;

	sign = (n < 0) ? -1 : 1;
	if (n < 0)
		n = -n;
	*p++ = sign * (n % 10) + '0';
	if (n > 0)
		itoa_r(n/10, p);
	*p = '\0';
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


/* ----------------------- Miscellaneous Functions ----------------------- */


/* getstr:  gets a line of input from keyboard */
static int getstr(char *s, int n)
{
	char *p = s;
	int c;

	while (n-- > 0 && (c = getchar()) != EOF && c != '\n')
		*p++ = c;
	if (c == '\n')
		*p++ = c;
	*p = '\0';
	return (int)(p-s);
}

/* get_input:  gets input with getstr; displays message first */
static int get_input(const char *msg, char *s, int lim)
{
	printf("%s", msg);
	return getstr(s, lim);
}


/* --------------- Functions to Convert to use pointers ------------------ */


/* shellsort:  sort v[0]...v[n-1] to increasing order */
static void shell_sort(int *v, int n)
{
	int gap, i, j, temp;

	for (gap = n/2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i-gap; j >= 0 && v[j] > v[j+gap]; j -= gap) {
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
}

/* alphasort:  sort string of characters in alphabetical order */
static void alpha_sort(char *s, int size)
{
	int i, tmp;
	unsigned char swapped;

	do {
		swapped = 0;
		for (i = 0; i < size-1; ++i) {
			if (s[i] > s[i+1]) {
				swapped = 1;
				tmp = s[i];
				s[i] = s[i+1];
				s[i+1] = tmp;
			}
		}
	} while (swapped);
}

/* expand:  expand a-z,A-Z,0-9 into the entire string of them */
static void expand(char *s1, char *s2)
{
	int i, j, k, count;

	for (i = j = 0; s1[i] != '\0'; i++) {
		if (s1[i+1] == '-' && s1[i+2] != '\0') {
			if (s1[i] < s1[i + 2]) {
				count = UP;
			} else {
				count = DOWN;
			}
			for (k = 0; s1[i] + k != s1[i + 2]; k += count, j++)
				s2[j] = s1[i] + k;
			i++;
		} else {
			s2[j++] = s1[i];
		}
	}
	s2[j] = '\0';
}

/* escape:  change newlines, tabs; into visible representation */
static int escape(char *s, char *t)
{
	int i, j;

	for (i = j = 0; t[i] != '\0'; ++i, ++j)
		switch (t[i]) {
			case '\n':
				s[j] = '\\';
				s[++j] = 'n';
				break;
			case '\t':
				s[j] = '\\';
				s[++j] = 't';
				break;
			default:
				s[j] = t[i];
				break;
		}
	s[j] = '\0';
	return j;
}

/* escape_r:  visible representation of newlines and tabs into characters */
static int rescape(char *s, char *t)
{
	int last, i, j;

	last = 0;
	for (i = 0, j = 0; t[i] != 0; ++j) {
		last = t[i];
		switch (last) {
		case '\\':
			++i;
			if (t[i] == 'n') {
				s[j] = '\n';
				++i;
			} else if (t[i] == 't') {
				s[j] = '\t';
				++i;
			}
			break;
		default:
			s[j] = last;
			i++;
			break;
		}
	}
	s[j] = '\0';
	return j;
}

/* htoi:  bitwise operation; convert hex string to decimal */
static unsigned int htoi(char *s)
{
	unsigned int val = 0;

	while (*s != 0) {
		char c = *s++;
		if (c >= '0' && c <= '9')
			c = (c - '0');
		else if (c >= 'a' && c <= 'z')
			c = (c - 'a') + 10;
		else if (c >= 'A' && c <= 'Z')
			c = (c - 'A') + 10;
		else
			return -1;
		val = (val << 4) | (c & 0x0f);
	}
	return val;
}

/* itob:  formats n as a base b integer in s */
static void itob(int n, char *s, int b)
{
	int sign;
	int i;

	sign = (n < 0) ? -1 : 1;
	i = 0;
	do {
		s[i++] = ((n % b) <= 9) ? \
		sign*(n % b)+'0' : sign*(n % b)+'a'-10;
	} while ((n /= b) != 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* rescapes:  remove all escape sequences from cstring */
static void rescapes(char *s)
{
	int len = str_len(s);
	char tmp[len+1];
	int i, j;

	i = j = 0;
	while (s[i] != 0 && i < len && j < len)
		switch (s[i]) {
		case NEWLINE: case TAB:
		case VTAB: case BACKSPACE:
		case BELL: case RETURN:
			++i;
			break;
		default:
			tmp[j++] = s[i++];
		}
	tmp[j] = '\0';
	str_cpy(s, tmp);
}

/* chtolt:  convert input character from regular text to 1337 5p34k */
static int chtolt(int c)
{
	switch (c) {
		case 'a': case 'A':
			c = '4';
			break;
		case 'e': case 'E':
			c = '3';
			break;
		case 'i': case 'I':
			c = '1';
			break;
		case 'o': case 'O':
			c = '0';
			break;
		case 's': case 'S':
			c = '5';
			break;
		case 'g': case 'G':
			c = '6';
			break;
		case 't': case 'T':
			c = '7';
			break;
		case 'b': case 'B':
			c = '8';
			break;
		case 'p': case 'P':
			c = '9';
			break;
		case 'z': case 'Z':
			c = '2';
			break;
		default:
			break;
	}

	return c;
}

/* leetconv:  convert s2 into leet speak in s1 */
static void leetconv(char *s1, char *s2)
{
	while ((*s1++ = chtolt(*s2++)) != 0);
	*s1 = '\0';
}

/* p_atof:  convert string s to double */
static double p_atof(char *s)
{
	double val, power;
	int i, sign;

	for (i=0; isspace(s[i]); i++);	/* skip while space */
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	return sign * val / power;
}

/* p_swap:  interchange v[i] and v[j] */
static void p_swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* p_qsort:  sort v[left]...v[right] into increasing order */
static void p_qsort(int v[], int left, int right)
{
	int i, last;

	if (left >= right)
		return;
	p_swap(v, left, (left + right)/2); /* move partition elem */
	last = left;
	for (i = left+1; i <= right; i++)	/* partition */
		if (v[i] < v[left])
			p_swap(v, ++last, i);
	p_swap(v, left, last);		/* restore partition elem */
	p_qsort(v, left, last-1);
	p_qsort(v, last+1, right);
}

#endif
