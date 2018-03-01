#include "../common/helper.h"

#define MAXOP	100	/* max size of operand or operator */
#define NUMBER	'0'	/* signal we have a numeric value */

extern int getop(char []);
extern void push(double);
extern double pop(void);

/* reverse Polish calculator */
int main()
{
	int type;
	double op2;
	char s[MAXOP];

	printf("Polish Calculator v0.1\nExpression: 2 1 - 3 5 + *\n"
		"Turns into: (2 - 1) * (3 + 5) = 7\n\n");
	printf("Expression >> ");
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() - pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("Error: zero divisor\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			printf("Expression >> ");
			break;
		default:
			printf("Error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
