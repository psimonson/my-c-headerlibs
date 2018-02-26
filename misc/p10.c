#include <stdio.h>
#include <stdlib.h>

int c_getline(char *s, int lim);
double calc(char c, float a, float b);

#define MAXLINE 64

/* program to calculate values from standard input */
int main()
{
	char s[MAXLINE];
	float a, b;
	char c;
	int i;

	a = b = 0;
	printf("Simple Calculator v0.01\n"
		"=======================\n");
	do {
		printf("Enter first number: ");
		i = c_getline(s, MAXLINE);
		a = atof(s);
		if (!(i > 0))
			continue;
		printf("Enter second number: ");
		i = c_getline(s, MAXLINE);
		b = atof(s);
		if (!(i > 0))
			continue;
		printf("Enter Calc Symbol (+,-,*,/): ");
		i = c_getline(s, MAXLINE);
		if (!(i > 0))
			break;
		c = s[0];
		if (!(i > 0))
			continue;
		printf("Result: %f\n", calc(c, a, b));
	} while (i != EOF && i > 0);
	return 0;
}

/* getline:  get line of input; from user */
int c_getline(char *s, int lim)
{
	int c, i;

	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	s[i] = 0;
	return i;
}

/* calc:  run through loop; calculating values */
double calc(char c, float a, float b)
{
	if (c == '+')
		return (double)(a + b);
	else if (c == '-')
		return (double)(a - b);
	else if (c == '*')
		return (double)(a * b);
	else if (c == '/')
		return (double)(a / b);
	return -1;
}
