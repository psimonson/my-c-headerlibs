#include "common/prs_string.h"

int main(int argc, char *argv[])
{
	char* last;
	char buf[MAXLINE];
	int running;

	running = 1;
	while (running) {
		if (last) free(last);
		printf("Enter your name: ");
		readln(buf, MAXLINE);
		last = str_dup(buf);
		printf("You typed: %s\n", buf);
		if (str_cmp(buf, "exit") == 0)
			running = 0;
	}
	printf("Last string typed was: %s\n", last);
	if (last) free(last);
	return 0;
}
