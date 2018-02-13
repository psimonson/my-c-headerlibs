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

int is_match(int left, int right)
{
	return ((left == ')' && right == '(') ||
			(left == ']' && right == '[') ||
			(left == '}' && right == '{'));
}

/* program to test c source files for minor syntax errors */
int main(int argc, char *argv[])
{
	stack_t *stack;
	FILE *file;
	int syntax_errors;
	int state;
	int error;
	size_t linenum;
	int c;

	stack = stack_create(8);
	if (stack == NULL)
		return -1;
	do_log(write_log, LOG_NAME, "Stack created!\n");
	if ((file = fopen(TEST_FILE, "rt")) == NULL) {
		do_log(append_log, LOG_NAME, "Error: Invalid file or cannot open.\n");
		stack_destroy(stack);
		return -1;
	}
	state = CODE;
	syntax_errors = error = linenum = 0;
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n' || c == '\r') {
			linenum++;
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
				int open = stack_popback(stack);
				if (!is_match(c, open)) {
					printf("Line %lu: Closing '%c' missing opening '%c'.\n",
						(unsigned long)linenum, c, open);
					do_log(append_log, LOG_NAME,
						"Line %lu: Closing '%c' missing opening '%c'.\n",
						(unsigned long)linenum, c, open);
					error = 1;
					syntax_errors += 1;
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
				(void)fgetc(file); /* an escaped char */
			} else {
				state = CODE;
			}
		break;
		case QUOTE2:
			if (c == '\\') {
				(void)fgetc(file); /* an escaped char */
			} else {
				state = CODE;
			}
		break;
		default:
		break;
		}
	}
	fclose(file);
	if (state == COMMENT) {
		printf("Code ends inside a comment!\n");
		do_log(append_log, LOG_NAME, "Code ends inside a comment!\n");
	} else if (state == QUOTE1) {
		printf("Code ends inside a single quote!\n");
		do_log(append_log, LOG_NAME, "Code ends inside a single quote!\n");
	} else if (state == QUOTE2) {
		printf("Code ends inside a double quote!\n");
		do_log(append_log, LOG_NAME, "Code ends inside a double quote!\n");
	}
	do_log(append_log, LOG_NAME, "File processed..."
		" syntax errors: %d\n", syntax_errors);
	fprintf(stderr, "File processed..."
		" syntax errors: %d\n", syntax_errors);
	stack_destroy(stack);
	do_log(append_log, LOG_NAME, "Stack destroyed.\n");
	return 0;
}
