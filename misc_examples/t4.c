#include "../common/helper.h"

#define MAXLINE 512

int main()
{
	char s1[MAXLINE];
	char s2[MAXLINE];
	int a;

	/* custom pstring manipulation */
	getstr(s1, MAXLINE);
	trim(s1);

	/* convert to int */
	printf("Before Conversions: %s\n", s1);
	a = p_atoi(s1);
	p_itoa(a, s2);

	printf("Conversion from string to int: %d\n", a);
	printf("Conversion from int to string: %s\n", s2);
	return 0;
}
