#include "../common/helper.h"

#define MAXLINE 64

/* program to get password */
int main()
{
	char s[MAXLINE];

	while (getstr(s, MAXLINE) > 0) {
		trim(s);
		if (str_cmp(s, "") == 0)
			break;
		else if (str_cmp(s, "thepass") == 0)
			printf("Correct!\n");
		else
			printf("Wrong!\n");
	}
	return 0;
}
