#include "../common/helper.h"

#define MAXLINE 64

/* program to get password */
int main()
{
	char s[MAXLINE];

	while (getline(s, MAXLINE) > 0) {
		trim(s);
		if (strcompare(s, "") == 0)
			break;
		else if (strcompare(s, "thepass") == 0)
			printf("Correct!\n");
		else
			printf("Wrong!\n");
	}
	return 0;
}
