#include "../common/helper.h"

#define MAXLINE 512

/* program to process a file or standard input */
int main()
{
	FILE *fin = NULL;
	char input[MAXLINE];
	char fname[MAXLINE];
	int c, len;

	printf("RemEscape v0.01 by Philip Simonson\n"
		"Removes escape codes from stdin or file stream.\n"
		"================================================\n\n");
	do {
		printf("What do you wish to do?\n"
			"1. Get Standard Input\n"
			"2. Get File Stream\n"
			"3. Exit\n\n"
			"Enter choice (1-3): ");
		getstr(input, MAXLINE);
		trim(input);
		c = input[0];
		switch (c) {
		case -2:
			break;
		case '1':
			printf("\n\nEnter a line of text below...\n");
			len = getstr(input, MAXLINE);
			if (len <= 0)
				printf("Could not get a line of input.\n");
			else {
/*				rescapes(input); */
				printf("Line below with escapes removed.\n%s\n", input);
			}
			p_zero(input, MAXLINE);
			break;
		case '2':
			printf("Enter filename: ");
			len = getstr(fname, MAXLINE);
			if (len <= 0)
				printf("No filename was given.\n");
			else {
				trim(fname);
				if ((fin = fopen(fname, "rt")) == NULL)
					printf("Cannot open file: %s\n", fname);
				else {
					while (fgets(input, MAXLINE-1, fin) != NULL) {
/*						rescapes(input);*/
						printf("%s\n", input);
					}
					fclose(fin);
				}
			}
			break;
		case '3':
			c = 0;
			break;
		default:
			printf("\nUnknown option: '%c'\n\n", c);
		}
	} while (c != 0);
	return 0;
}
