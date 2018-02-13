#include "../common/logger.h"
#include "../common/sstack.h"

#define LOG_NAME "log7.txt"
#define TEST_FILE "test1.c"

const char key[] = "298374dkfjlsdjfsdkjf893uFKJDFJF";

enum {
	CODE,
	COMMENT,
	QUOTE1,
	QUOTE2
};

/* program to test c source files for minor syntax errors */
int main(int argc, char *argv[])
{
	stack_t *stack;
	FILE *file;
	int state;
	int error;
	size_t line;
	int c;

	stack = stack_create(8);
	if (stack == NULL)
		return -1;

	do_log(write_log, LOG_NAME, "Stack created... checking source.\n");
	if ((file = fopen(TEST_FILE, "rt")) == NULL) {
		stack_destroy(stack);
		return -1;
	}
	state = CODE;
	error = 0;
	line = 1;
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n') {
			line++;
		}

		switch (state) {
			case CODE:
				if (c == '\'') {
					state = QUOTE1;
				} else if (c == '"') {
					state = QUOTE2;
				} else if (c == '/') {
					int second = fgetc(file);
					if (second == '*') {
						state = COMMENT;
					} else {
						ungetc(second, file);
					}
				} else if (c == '(' || c == '[' || c == '{') {
					stack_pushback(stack, c, -1);
				} else if (c == ')' || c == ']' || c == '}') {
					if (stack_is_empty(stack)) {
						printf("Line %lu: Closing '%c' found without counterpart.\n",
							(unsigned long)line, c);
						do_log(append_log, LOG_NAME, "Line %lu: Closing '%c'"
							" found without counterpart.\n",
							(unsigned long)line, c);
						error = 1;
					} else {
						int open = stack_popback(stack);
						if ((c == ')' && open != '(') ||
							(c == ']' && open != '[') ||
							(c == '}' && open != '{')) {
							printf("Line %lu: Closing '%c' does not match "
								"opening '%c'.\n", (unsigned long)line, c, open);
							do_log(append_log, LOG_NAME, "Line %lu: Closing '%c'"
								" does not match opening '%c'.\n",
								(unsigned long)line, c, open);
							error = 1;
						}
					}
				}
			break;
			case COMMENT:
				if (c == '*') {
					int second = fgetc(file);
					if (second == '/') {
						state = CODE;
					} else {
						ungetc(second, file);
					}
				}
			break;
			case QUOTE1:
				if (c == '\\') {
					(void)fgetc(file);	/* an escaped char inside '' throw it away */
				} else if (c == '\'') {
					state = CODE;
				}
			break;
			case QUOTE2:
				if (c == '\\') {
					(void)fgetc(file);
				} else if (c == '"') {
					state = CODE;
				}
			break;
			default:
			break;
		}
	}
	fclose(file);
	if (state == COMMENT) {
		printf("Code ends inside comment!\n");
		do_log(append_log, LOG_NAME, "Code ends inside comment!\n");
	} else if (state == QUOTE1) {
		printf("Code ends inside single quotes!\n");
		do_log(append_log, LOG_NAME, "Code ends inside single quotes.\n");
	} else if (state == QUOTE2) {
		printf("Code ends inside double quotes!\n");
		do_log(append_log, LOG_NAME, "Code ends inside double quotes.\n");
	} else if (stack_is_empty(stack) && error == 0) {
		printf("Code seems to be ok.\n");
		do_log(append_log, LOG_NAME, "Code seems to be ok.\n");
	}
	if (!stack_is_empty(stack)) {
		while (!stack_is_empty(stack)) {
			c = stack_popback(stack);
			printf("Opening '%c' found without counterpart.\n", c);
			do_log(append_log, LOG_NAME, "Opening '%c' found without "
				"counterpart.\n", c);
		}
	}
	stack_destroy(stack);
	do_log(append_log, LOG_NAME, "Stack destroyed, program exited normally.\n");
	return 0;
}
