#include "../common/logger.h"
#include "../common/sstack.h"

#define LOG_NAME "log7.txt"
#define TEST_FILE "test1.c"

const char key[] = "298374dkfjlsdjfsdkjf893uFKJDFJF";

int is_match(int left, int right)
{
	return ((left == '{' && right == '}') ||
			(left == '(' && right == ')') ||
			(left == '[' && right == ']') ||
			(left == '<' && right == '>'));
}

/* program to test c source files for minor syntax errors */
int main(int argc, char *argv[])
{
	stack_t *stack;
	stack_t *stack_ln;
	FILE *file;
	int syntax_errors;
	int linenum;
	int c;

	stack = stack_create(8);
	stack_ln = stack_create(8);
	if (stack == NULL)
		return -1;
	if (stack_ln == NULL) {
		stack_destroy(stack);
		return -1;
	}
	do_log(write_log, LOG_NAME, "Stack created!\n");
	if ((file = fopen(TEST_FILE, "rt")) == NULL) {
		do_log(append_log, LOG_NAME, "Error: Invalid file or cannot open.\n");
		stack_destroy(stack);
		return -1;
	}
	syntax_errors = linenum = 0;
	while ((c = fgetc(file)) != EOF) {
		switch (c) {
		case '\n':
		case '\r':
			++linenum;
		break;
		case '{':
		case '(':
		case '[':
		case '<':
			stack_pushback(stack, c, -1);
			stack_pushback(stack_ln, linenum, -1);
		break;
		}
		if (c == '>' || c == ']' || c == ')' || c == '}') {
			int left_linenum;
			int left;
			left = stack_popback(stack);
			left_linenum = stack_popback(stack_ln);
			if (!is_match(left, c)) {
				do_log(append_log, LOG_NAME, "Syntax error : %c doesn't match"
					" %c : line %d\n", left, c, left_linenum);
				fprintf(stderr, "Syntax error : %c doesn't match %c : line %d\n",
					left, c, left_linenum);
				syntax_errors += 1;
			}
		}
	}
	fclose(file);
	stack_destroy(stack);
	stack_destroy(stack_ln);
	if (syntax_errors > 0) {
		do_log(append_log, LOG_NAME, "File processed..."
			" syntax errors: %d\n", syntax_errors);
		fprintf(stderr, "File processed..."
			" syntax errors: %d\n", syntax_errors);
	} else {
		do_log(append_log, LOG_NAME, "File processed... no syntax errors.\n");
		fprintf(stderr, "File processed... no syntax errors.\n");
	}
	do_log(append_log, LOG_NAME, "Stack destroyed.\n");
	return 0;
}
