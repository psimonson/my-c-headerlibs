#include "../common/helper.h"

#define MAXLINE 512

int main(int argc, char *argv[])
{
	char* last;
	char buf[MAXLINE];
	int running;

	last = NULL;
	running = 1;
	while (running) {
		if (last) free(last);
		printf("Enter your name: ");
		getstr(buf, MAXLINE);
		last = str_dup(buf);
		printf("You typed: %s\n", buf);
		if (str_cmp(buf, "exit") == 0)
			running = 0;
	}
	printf("Last string typed was: %s\n", last);
	if (last) free(last);
	return 0;
}
