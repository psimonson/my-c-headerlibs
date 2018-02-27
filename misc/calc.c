#include "../common/helper.h"

#define MAXLINE 100

/* rudimentary calculator */
int main()
{
	char line[MAXLINE];
	double sum;

	sum = 0;
	while (getline(line, MAXLINE) > 0) {
		trim(line);
		if (strcompare(line, "") == 0)
			break;
		printf("\t%g\n", sum += atof(line));
	}
	return 0;
}
