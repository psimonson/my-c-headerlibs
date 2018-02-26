#include <stdio.h>

int c_getline(char s[], int lim);
int strcmp(const char s1[], const char s2[]);

#define MAXLINE 64

/* program to get password */
int main()
{
	char s[MAXLINE];

	while (c_getline(s, MAXLINE) > 0)
		if (strcmp("thepass", s) == 0)
			printf("Correct!\n");
		else
			printf("Wrong!\n");
	return 0;
}

/* getline:  get input line; from stdin */
int c_getline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	s[i] = 0;
	return i;
}

/* strcmp: compares s1 to s2; return 0 if they match */
int strcmp(const char s1[], const char s2[])
{
	int i;

	for (i = 0; s1[i] != 0 && s2[i] != 0; ++i)
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return 0;
}
