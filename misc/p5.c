#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int prs_main() {
	printf("Hello from prs_main!\n");
	return 0;
}

int user_main(int argc, char *argv[]) {
	int i;

	printf("Hello from user_main()\n");
	printf("Arguments Below:\n\n");
	for (i = 1; i < argc; i++) {
		printf("[arg %d] ", i);
		printf("%s", argv[i]);
		printf("\n");
	}
	printf("\nEnd of arguments.\n");
	return 0;
}

void set_func(int a, int *, char **, int (*)());
void die(int, const char *, ...);

#define LOG_ERROR "[ERROR] : "
#define LOG_DEBUG "[DEBUG] : "

#define MAIN_NOARGS 0
#define MAIN_WARGS  1

int main(int argc, char *argv[]) {
#if defined(DEBUG)
	printf(LOG_DEBUG "Entering prs_main()\n");
#endif
	set_func(MAIN_NOARGS, NULL, NULL, &prs_main);
#if defined(DEBUG)
	printf(LOG_DEBUG "Done with prs_main()\n");
	printf(LOG_DEBUG "Entering user_main()\n");
#endif
	set_func(MAIN_WARGS, &argc, argv, &user_main);
#if defined(DEBUG)
	printf(LOG_DEBUG "Done with user_main()\n");
#endif
	return 0;
}

void set_func(int a, int *argc, char *argv[], int (*func)()) {
	switch (a) {
		case MAIN_NOARGS:
			(*func)();
		break;
		case MAIN_WARGS:
			if (argc == NULL || argv == NULL)
				die(1, LOG_ERROR "No arguments given.\n");
			(*func)(*argc, argv);
		break;

		default:
			fprintf(stderr, LOG_ERROR "Not a type of main.\n");
	}
}

void die(int r, const char *msg, ...) {
	va_list args;
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);
	exit(r);
}

