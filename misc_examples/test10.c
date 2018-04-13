#include "../common/queue.h"
#include "../common/stack.h"

#define MAXLINE	1024

enum STATE {
	CODE,
	COMMENT,
	QUOTES
};
typedef enum STATE state_t;

/* global variables */
char line[MAXLINE];			/* global line variable */
stack_t stack;				/* stack for <, (, [, { */
queue_t queue;				/* queue for >, ), ], } */
state_t state;				/* state variable */
int err_count;				/* how many errors occurred */
int comments;				/* comment count */
int quotes;					/* quotes count */
int error;					/* error flag */

/* program functions */
int getln(FILE *file);
int check_source(FILE *file);

/* program to check the source code for errors */
int main(int argc, char **argv)
{
	FILE *file;

	if (argc == 2 || argc > 3) {
		printf("Usage: %s [-f filename.ext]\n", argv[0]);
		return 1;
	}

	if (argc == 1) {
		check_source(stdin);
	} else {
		if (*argv[1] == '-') {
			while (*++argv[1]) {
				switch (*argv[1]) {
				case 'f':
					if ((file = fopen(argv[2], "rt")) == NULL) {
						printf("Cannot open file for reading.\n");
						return 2;
					}
					check_source(file);
					fclose(file);
					printf("File processed!\n");
				break;
				default:
					printf("Unknown option '%c'\n", *argv[1]);
				break;
				}
			}
		}
	}
	return 0;
}

/* getln:  get line of input from stdin */
int getln(FILE *file)
{
	extern char line[];
	int c, i;
	for (i = 0; i < MAXLINE-2 && (c = fgetc(file)) != EOF && c != '\n'; i++)
		line[i] = c;
	if (c == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return i;
}

/* is_match:  checks for matching chars */
int is_match(int c1, int c2)
{
	return ((c1 == '<' && c2 != '>') ||
			(c1 == '(' && c2 != ')') ||
			(c1 == '[' && c2 != ']') ||
			(c1 == '{' && c2 != '}'));
}

/* special_body:  prints output for syntax checker */
void report(void)
{
	extern queue_t queue;
	extern state_t state;
	extern int comments;
	extern int quotes;
	extern int error;
	extern int err_count;


	if (state == COMMENT) {
		printf("Code ends inside of comment.\n");
		error = 1;
	} else if (state == QUOTES) {
		printf("Code ends inside of quotes.\n");
		error = 1;
	} else if (stack_is_empty(&stack) && queue_is_empty(&queue) && error == 0) {
		printf("Code seems to be okay.\n");
		printf("Comments: %d\nQuotes: %d\n", comments, quotes);
	} else if (error == 1) {
		while (!queue_is_empty(&queue)) {
			int val, pos;
			queue_get(&queue, &val, &pos);
			printf("Syntax error line %d : '%c' missing counterpart.\n",
				pos, val);
			error = 1;
			++err_count;
		}
		printf("Syntax errors in file: %d\n", err_count);
		printf("There were errors in the code.\n");
	}
}

/* check_source:  checks source code for syntax errors */
int check_source(FILE *file)
{
	extern char line[];
	extern queue_t queue;
	extern state_t state;
	extern int comments;
	extern int quotes;
	extern int error;
	extern int err_count;
	int c, d, i;
	int ln, len;

	error = 0;
	ln = 0;
	comments = quotes = 0;
	while ((len = getln(file)) > 0) {
		++ln;
		i = 0;
		while (i < len && (c = line[i++]) != EOF) {
			switch (state) {
			case CODE:
				if (c == '\'' || c == '"') {
					state = QUOTES;
					break;
				} else if (c == '/') {
					d = line[i++];
					if (d == '*') {
						state = COMMENT;
						break;
					}
				} else if (c == '<' || c == '(' || c == '[' || c == '{') {
					queue_add(&queue, c, ln);
				} else if (c == '>' || c == ')' || c == ']' || c == '}') {
					if (queue_is_empty(&queue)) {
						printf("Syntax error on line %d : '%c' missing"
							" counterpart.\n", ln, c);
						error = 1;
						err_count++;
					} else {
						int val, pos;
						queue_get(&queue, &val, &pos);
						if (is_match(c, val)) {
							printf("Syntax error on line %d : '%c' missing"
								" '%c'.\n", ln, val, c);
							error = 1;
							err_count++;
						}
					}
				}
			break;
			case QUOTES:
				if (c == '\\')
					continue;
				else if (c == '\'' || c == '"') {
					quotes++;
					state = CODE;
				}
			break;
			case COMMENT:
				if (c == '*') {
					d = line[i++];
					if (d == '/') {
						comments++;
						state = CODE;
					}
				}
			break;
			}
		}
	}

	report();
	return 0;
}
