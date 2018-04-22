/*
 ********************************************************************
 * helper.h - simple helper functions that I commonly use.
 *
 * Date: 11/13/2017
 * Create by Philip '5n4k3' Simonson
 ********************************************************************
 */


#ifndef PRS_HELPER_H
#define PRS_HELPER_H

/* ------------------------ Include Headers -------------------------- */


#include <stdio.h>
#include <ctype.h>


/* ------------------------- Enumerations ---------------------------- */


enum boolean { NO, YES };
enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t',
		NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };
enum getln_types { GETLN_TYPE_NONE = -1, GETLN_TYPE_NORMAL,
		GETLN_TYPE_IGNORE };

typedef enum boolean bool_t;


/* ------------------------- Global Defines -------------------------- */


#define TRUE 1
#define FALSE 0
#define true TRUE
#define false FALSE

#define UP 1
#define DOWN -1


/* ------------------------ String Functions ------------------------- */


/* p_zero:  zero memory block */
static void p_zero(void *s, int size)
{
	int i;

	for (i = 0; i < size; ++i)
		((char*)s)[i] = 0;
}

/* getstr:  gets user input from stdin */
static int getstr(char *s, int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* strlength:  returns the length of a string */
static int strlength(const char s[])
{
	int i;

	for (i = 0; s[i] != '\0'; i++);
	return i;
}

/* strindex:  return index of t in s, -1 if none */
static int strindex(char *s, const char *t)
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++);
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

/* shellsort:  sort v[0]...v[n-1] to increasing order */
static void shellsort(int v[], int n)
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
static void alphasort(char s[], int size)
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

/* reverse:  reverse s inplace */
static void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlength(s)-1; i < j && j > 0; ++i, --j)
		c = s[j], s[j] = s[i], s[i] = c;
}

/* expand:  expand a-z,A-Z,0-9 into the entire string of them */
static void expand(char s1[], char s2[])
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

/* p_itoa:  converts integer to string */
static void p_itoa(int n, char s[])
{
	int i;
	int sign;

	sign = (n < 0) ? -1 : 1;
	i = 0;
	do {	/* generate digits in revverse order */
		s[i++] = sign * (n % 10) + '0';	/* get next digit */
	} while ((n /= 10) != 0);	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* trim:  trims newlines, blanks, tabs off string */
static void trim(char s[])
{
	int i;

	for (i = strlength(s)-1; i >= 0; i--)
		if (s[i] == '\t' || s[i] == '\n')
			break;
	s[i] = '\0';
}

/* escape:  change newlines, tabs; into visible representation */
static int escape(char s[], char t[])
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
static int escape_r(char s[], char t[])
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


/* ------------------------ Miscellaneous Functions ------------------------- */


/* htoi:  bitwise operation; convert hex string to decimal */
static int htoi(char *s)
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
static void itob(int n, char s[], int b)
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

/* itoa2:  converts integer to string */
static void itoa2(int n, char s[], int w)
{
	int i;
	int sign;

	sign = (n < 0) ? -1 : 1;
	do {	/* generate digits in revverse order */
		s[i++] = sign * (n % 10) + '0';	/* get next digit */
	} while ((n /= 10) != 0);	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	while (i <= w)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}

/* strcompare:  compare s1 to s2; returns s2-s1 */
static int strcompare(char s1[], char s2[])
{
	int i, j;

	for (i = j = 0; i < strlength(s1) || j < strlength(s2); i++, j++)
		if (s1[i] != s2[j])
			return s2[j] - s1[i];
	return 0;
}



/* strcopy:  copies a string to another string */
static int strcopy(char s1[], char s2[], int size)
{
	int i, j;

	for (i = j = 0; i < size-1 && s2[j] != 0; i++, j++)
		s1[i] = s2[j];
	s1[i] = '\0';
	return i;
}

/* memmove:  move memory to another location */
static int memcopy(void *s1, void *s2, int size)
{
	int i, j;

	for (i = j = 0; i < size && j < size; i++, j++)
		((char *)s1)[i] = ((char *)s2)[j];
	return i;
}

/* rescapes:  remove all escape sequences from cstring */
static void rescapes(char s[])
{
	int len = strlength(s);
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
	strcopy(s, tmp, strlength(tmp)+1);
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
static void leetconv(char s1[], char s2[])
{
	int i, j;

	for (i = j = 0; s2[j] != 0; ++i, ++j)
		s1[i] = chtolt(s2[j]);
	s1[i] = '\0';
}

/* strindex_r:  returns index of t in s, -1 if none; in reverse */
static int strindex_r(char s[], const char t[])
{
	int i, j, k;

	for (i = strlength(s)-1; i >= 0; i--) {
		for (j = i, k = strlength(t)-1; k >= 0 && j >= 0 && s[j] == t[k]; j--, k--);
		if (k < 0)
			return i;
	}
	return -1;
}

/* p_atof:  convert string s to double */
static double p_atof(char s[])
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

/* p_atoi:  convert string s to integer */
static int p_atoi(char s[])
{
	return (int)p_atof(s);
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

/* reverse_r:  reverse a string; recursively */
static void reverse_r(char s[])
{
	static int i = 0;
	static int j = -1;
	char temp;

	if (j < 0)	/* check initial value of j < 0 */
		j = strlength(s) - 1;	/* if j < 0 set to end of string */
	if (j - i > 0) {
		temp = s[j];	/* store char at s[j] */
		s[j] = s[i];	/* write char at s[i] to s[j] */
		s[i] = temp;	/* write temp back to s[i] */
		--j, ++i;	/* increment j and i */
		reverse_r(s);	/* run recursively */
	} else {
		i = 0;		/* reset i back to 0 */
		j = -1;		/* reset j back to -1 */
	}
}

/* itoa_r:  convert int to string; recursively */
static void itoa_r(int n, char s[])
{
	int i, sign;

	i = 0;
	if ((sign = n) < 0)
		n = -n;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse_r(s);
}

#endif
