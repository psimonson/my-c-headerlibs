#include <stdio.h>
#include <stdlib.h>

#define LOG_ERROR "[ERROR] : "
#define LOG_DEBUG "[DEBUG] : "

#define IN	  1
#define OUT	  0

int die(const char *);

int main(void) {
	int c, nc, state;
	FILE *f;

	if ((f = fopen("data.tmp", "w")) == NULL)
		die(LOG_ERROR "Cannot open output file for writing.\n");
	nc = 0;
	state = OUT;
	while ((c = getchar()) != EOF) {
		++nc;
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
			fputc('\n', f);
		} else if (state == OUT)
			state = IN;
		if (c == ' ' || c == '\n' || c == '\t')
			continue;
		fputc(c, f);
	}
	fclose(f);
	return 0;
}

int die(const char *msg) {
	fprintf(stderr, "Error: %s\n", msg);
	exit(0);
	return 0;
}
