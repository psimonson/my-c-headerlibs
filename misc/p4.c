#include <stdio.h>

#define IN  1
#define OUT 0

int getw_file();

int main()
{
	char s[128];

	getw_file(stdin, s, 128);
	printf("%s", s);

	return 0;
}

int getw_file(FILE *in, char *word, int size)
{
	int c, i, state;

	i = 0;
	state = OUT;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
			continue;
		} else if (state == OUT) {
			state = IN;
		}
		if (c == '\n') {
			word[i] = 0;
			break;
		}
		if (i < size)
			word[i] = c;
		++i;
	}
	return 0;
}
