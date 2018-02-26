#include "../common/helper.h"

void tests(void);	/* test all functions */

/* program to run tests */
int main()
{
	tests(); /* test functions */

	return 0;
}

/* repstr:  convert string to upper or lower */
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
	if (strcompare(s1, "HELLO WORLD!") == 0)
		++passed;
	else
		printf("Test 1 - (func isupper) failed.\n");

	/* test1 - func toupper */
	repstr(s2, 13, 0);
	if (strcompare(s2, "hello world!") == 0)
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
	if (isdigit(c))
		++passed;
	else
		printf("Test 1 - (func isnum) failed.\n");

	c = 0;
	if (isdigit(c))
		++passed;
	else
		printf("Test 2 - (func isnum) failed.\n");

	/* All tests done display results */
	printf("Tests %d passed out of %d test%s.\n",
		passed, MAXTESTS, (passed > 1) ? "s" : "");
}
