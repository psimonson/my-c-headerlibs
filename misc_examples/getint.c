#include "../common/helper.h"

int getch(void);
void ungetch(int);

int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch()));
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 100

int main()
{
	int n, array[BUFSIZE];

	for (n=0; n < BUFSIZE && getint(&array[n]) != EOF; n++);
	printf("*** Numbers listed in reverse order below ***\n");
	while (n >= 0)
		printf("%d ", array[n--]);
	printf("\n*** End of listed numbers ***\n");
	return 0;
}

char buf[BUFSIZE];	/* getch buffer */
int bufp = 0;		/* getch buffer position */

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("getch: buffer limit reached.\n");
	else
		buf[bufp++] = c;
}
