#include <stdio.h>

int tolower(int c);	/* to lower-case */
int toupper(int c);	/* to upper-case */
int isalpha(int c);	/* is alpha? */
int isnum(int c);	/* is number? */
void tests(void);	/* test all functions */

int main()
{
	tests(); /* test functions */

	return 0;
}

int tolower(int c)
{
	return (c >= 'A' && c <= 'Z') ? (c - 'A') + 'a' : c;
}

int toupper(int c)
{
	return (c >= 'a' && c <= 'z') ? (c - 'a') + 'A' : c;
}

int isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z')) ? 1 : 0;
}

int isnum(int c)
{
	return (c >= 0 && c <= 9) ? 1 : 0;
}

int strcmp(char *s1, char *s2)
{
	int i, j;

	for (i = 0, j = 0; s1[i] != 0; i++, j++)
		if (s1[i] != s2[j])
			return (s1[i] - s2[j]);
	return 0;
}

void repstr(char s[], int len, char t)
{
	int c, i;

	for (i = 0; i < len; ++i) {
		c = s[i];
		s[i] = (t) ? toupper(c) : tolower(c);
	}
	s[i] = 0;
}

#define MAXTESTS 6

void tests(void)
{
	char s1[] = "Hello world!";
	char s2[] = "HELLO WORLD!";
	int c, passed = 0;

	/* test1 - func tolower */
	repstr(s1, 13, 1);
	if (strcmp(s1, "HELLO WORLD!") == 0)
		++passed;
	else
		printf("Test 1 - (func isupper) failed.\n");

	/* test1 - func toupper */
	repstr(s2, 13, 0);
	if (strcmp(s2, "hello world!") == 0)
		++passed;
	else
		printf("Test 1 - (func islower) failed.\n");

	/* test1 - func isalpha */
	c = 'a';
	if (isalpha(c))
		++passed;
	else
		printf("Test 1 - (func isalpha) failed.\n");

	/* test2 - func isalpha */
	c = 0;
	if (isalpha(c))
		++passed;
	else
		printf("Test 2 - (func isalpha) failed.\n");

	/* test1 - func isnum */
	c = 'a';
	if (isnum(c))
		++passed;
	else
		printf("Test 1 - (func isnum) failed.\n");

	c = 0;
	if (isnum(c))
		++passed;
	else
		printf("Test 2 - (func isnum) failed.\n");

	/* All tests done display results */
	printf("Tests %d passed out of %d test%s.\n",
		passed, MAXTESTS, (passed > 1) ? "s" : "");
}
