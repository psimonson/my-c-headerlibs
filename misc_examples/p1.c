#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_ERROR	"[ERROR] : "
#define LOG_DEBUG	"[DEBUG] : "
#define LOG_INFO	"[INFO]  : "

#define IN		1	/* inside a word */
#define OUT		0	/* outside a word */

int die(const char *);

/* program to take a string from input,
 * tokenizing string (splitting into tokens)
 */
int main(void) {
	int c, i, nc, nw, state;
	char s[BUFSIZ];

	state = OUT;
	nc = nw = 0;
	memset(s, 0, sizeof s);
	while ((c = getchar()) != EOF) {
		s[nc] = c;
		++nc;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("Last string was:\n%sString below tokenized...\n", s);
	state = OUT;
	for (i = 0; i < nc; i++) {
		putchar(s[i]);
		if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') {
			state = OUT;
			putchar('\n');
		} else if (state == OUT)
			state = IN;
	}
	printf("Total words: %d\nTotal chars: %d\n", nw, nc);
	return 0;
}

int die(const char *msg) {
	fprintf(stderr, "Error: %s\n", msg);
	exit(0);
	return 0;
}

