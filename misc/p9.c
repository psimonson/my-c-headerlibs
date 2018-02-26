#include <stdio.h>

/* hex string to decimal */
unsigned long hex2long(char *s);
/* custom getline function (no-newline) */
int c_getline(char *s, int lim);

#define MAXLINE 256

/* program to convert hex to decimal and print the result */
int main()
{
	char s[MAXLINE];	/* store hex string here */
	long x;			/* store hex2long conversion here */
	int i;			/* store length of string here */

	printf("Hex converter v0.01\n"
		"===================\n\n"
		"Valid hex digits (0-9,a-f,A-F)\n");
	do {
		printf("Type a hex number: ");
		i = c_getline(s, MAXLINE);	/* getline from user */
		if (i <= 0)		/* if i <= 0 then */
			continue;	/* recheck condition */
		x = hex2long(s);	/* do the conversion */
		if (x >= 0)	/* compare x >= 0 (print result) */
			printf("Decimal: %ld\n", x);
		else		/* else report hex value needed */
			printf("You need to enter a hex value.\n");
	} while (i > 0);	/* exit loop when i <= 0 */
	return 0;		/* exit success */
}

/* getline:  get line of input from user; without newline */
int c_getline(char *s, int lim)
{
	int c, i;

	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	s[i] = 0;
	return i;
}

/* hex2long:  convert hex string into long integer */
unsigned long hex2long(char *s)
{
	unsigned long x;

	x = 0;
	while (*s) {
		char byte = *s++;
		if (byte >= 'A' && byte <= 'F')
			byte = (byte - 'A') + 10;
		else if (byte >= 'a' && byte <= 'f')
			byte = (byte - 'a') + 10;
		else if (byte >= '0' && byte <= '9')
			byte -= '0';
		else
			return -1;
		x = (x << 4) | (byte & 0x0f);
	}
	return x;
}
