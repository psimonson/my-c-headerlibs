#include "../common/helper.h"

#define MAXLINE 512

int main()
{
	char s1[MAXLINE];
	char s2[MAXLINE];
	int a;

	/* custom pstring manipulation */
	getline(s1, MAXLINE);
	trim(s1);

	/* convert to int */
	printf("Before Conversions: %s\n", s1);
	a = atoi(s1);
	itoa(a, s2);

	printf("Conversion from string to int: %d\n", a);
	printf("Conversion from int to string: %s\n", s2);
	return 0;
}
