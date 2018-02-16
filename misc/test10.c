#include "../common/queue.h"

#define MAXLINE	1024

enum STATE {
	CODE,
	COMMENT,
	QUOTES
};
typedef enum STATE state_t;

/* global variables */
char line[MAXLINE];			/* global line variable */
queue_t queue;				/* global queue */
state_t state;				/* state variable */
int comments;				/* comment count */
int quotes;					/* quotes count */
int error;					/* error flag */

/* program functions */
int getln(void);
int check_source(void);

/* program to check the source code for errors */
int main(int argc, char **argv)
{
	check_source();
	return 0;
}

/* getln:  get line of input from stdin */
int getln(void)
{
	extern char line[];
	int c, i;
	for (i = 0; i < MAXLINE-2 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;
	if (c == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return i;
}

/* is_match:  checks for matching chars */
int is_match(int c1, int c2)
{
	return ((c1 == '(' && c2 != ')') ||
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

	if (comments > 0 || quotes > 0)
		printf("Comments: %d\nQuotes: %d\n", comments, quotes);
	if (state == COMMENT) {
		printf("Code ends inside of comment.\n");
		error = 1;
	} else if (state == QUOTES) {
		printf("Code ends inside of quotes.\n");
		error = 1;
	} else if (queue_is_empty(&queue) && error == 0) {
		printf("Code seems to be okay.\n");
	} else {
		while (!queue_is_empty(&queue)) {
			int val, pos;
			queue_get(&queue, &val, &pos);
			printf("Syntax error: line %d : '%c' missing"
				" counterpart.\n", pos, val);
		}
		printf("There were errors in the code.\n");
	}
}

/* check_source:  checks source code for syntax errors */
int check_source(void)
{
	extern char line[];
	extern queue_t queue;
	extern state_t state;
	extern int comments;
	extern int quotes;
	extern int error;
	int c, d, i;
	int ln, len;

	error = 0;
	ln = 0;
	comments = quotes = 0;
	while ((len = getln()) > 0) {
		++ln;
		i = 0;
		while (i < len && (c = line[i++]) != EOF) {
			switch (state) {
			case CODE:
				if (c == '\'' || c == '"') {
					state = QUOTES;
					break;
				}
				if (c == '/') {
					d = line[i++];
					if (d == '*') {
						state = COMMENT;
						break;
					}
				}
				if (c == '(' || c == '[' || c == '{') {
					queue_add(&queue, c, ln);
				} else if (c == ')' || c == ']' || c == '}') {
					if (queue_is_empty(&queue)) {
						printf("Syntax error: line %d : '%c' missing "
							"counterpart.\n", ln, c);
						error = 1;
					} else {
						int val, pos;
						queue_get(&queue, &val, &pos);
						if (is_match(c, val)) {
							printf("Syntax error: line %d: '%c' missing "
								"'%c'\n", ln, val, c);
							error = 1;
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
