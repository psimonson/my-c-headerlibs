#include "../common/helper.h"

#define MAXLINE 512

int main()
{
	char s1[MAXLINE];
	int num;

	getstr(s1, MAXLINE);
	num = htoi(s1);
	printf("%s = %d\n", s1, num);

	return 0;
}
