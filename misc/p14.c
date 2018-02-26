#include "../common/helper.h"

#define MAXLINE 512

#define FIRST 0
#define SECOND 1
#define THIRD 2
#define FOURTH 3
#define END 4

/* program to convert escapes into visible characters and back */
int main()
{
	FILE *fin, *fout;
	char fname[MAXLINE];
	char input[MAXLINE];
	char output[MAXLINE];
	char state, type;


	printf("Escape v0.01 by Philip R Simonson\n"
		"Program to convert escape sequences in files\n"
		"=============================================\n\n");

	type = -1;
	state = FIRST;
	do {
		switch (state) {
			case FIRST:
				printf("Type \"escapes\" or \"no escapes\" or \"exit\" to quit.\n"
					"escapes\t - change all '\\n', '\\t', etc. to printable characters.\n"
					"no escapes - change all escapes to visible characters\n\n");
				printf("Enter type: ");
				getline(input, MAXLINE);
				trim(input);
				if (strcompare(input, "") == 0)
					printf("You need to enter some text.\n\n");
				else {
					if (strcompare(input, "escapes") == 0) {
						printf("Adding escape sequences...\n");
						type = 0;
						state = SECOND;
					} else if (strcompare(input, "no escapes") == 0) {
						printf("Replacing escape sequences...\n");
						type = 1;
						state = SECOND;
					} else if (strcompare(input, "exit") == 0) {
						printf("Quitting program...\n");
						state = END;
					} else {
						printf("That was not a valid entry.\n\n");
						type = -1;
					}
				}
				break;
			case SECOND:
				printf("Enter input file name: ");
				getline(fname, MAXLINE);
				trim(fname);
				if (strcompare(fname, "") == 0) {
					state = END;
				} else {
					if ((fin = fopen(fname, "rt")) == NULL) {
						printf("Cannot open: %s\nFor reading...\n", fname);
						state = FIRST;
					}
					state = THIRD;
				}
				break;
			case THIRD:
				printf("Enter output file name: ");
				getline(fname, MAXLINE);
				trim(fname);
				if (strcompare(fname, "") == 0) {
					state = END;
				} else {
					if ((fout = fopen(fname, "wt")) == NULL) {
						printf("Cannot open: %s\nFor writing...\n", fname);
						state = FIRST;
					}
					state = FOURTH;
				}
				break;
			case FOURTH:
				/* process here */
				while (fgets(input, MAXLINE-1, fin) != NULL) {
					if (type == 0)
						escape_r(output, input);
					else
						escape(output, input);
					fputs(output, fout);
				}
				fclose(fin);
				fclose(fout);
				printf("File %s written.\n", fname);
				state = FIRST;
				break;
			default:
				break;
		}
	} while (state != END);

	return 0;
}
