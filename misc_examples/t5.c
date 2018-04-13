#include "../common/helper.h"

#define MAXLINE 512

/* program to get file input and remove escapes */
int main()
{
	char s[MAXLINE];

	printf("Enter a string: ");
	getstr(s, MAXLINE);
	rescapes(s);
	printf("All escape sequences removed...\n%s\n",
			s);
	return 0;
}
