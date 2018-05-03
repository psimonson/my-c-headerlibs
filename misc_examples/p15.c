#include "../common/helper.h"

#define MAXLINE 512

enum states { DEFAULT = -1, FIRST, SECOND, CONVERT };

/* program to convert normal plain text into leet speak */
int main()
{
	FILE *fin = NULL, *fout = NULL;
	char input[MAXLINE];
	char output[MAXLINE];
	int answer, state;

	printf("Leet Speak Converter v0.01\n"
		"Converts normal text lines into leet speak.\n"
		"===========================================\n\n");
	state = DEFAULT;
	do {
		switch (state) {
		case FIRST:
			printf("Enter input filename: ");
			getstr(input, MAXLINE);
			trim(input);
			if (str_cmp(input, "") == 0) {
				printf("You must input a filename.");
				state = DEFAULT;
			} else {
				if ((fin = fopen(input, "rt")) == NULL) {
					printf("Sorry couldn't open file: %s\n",
						input);
					state = DEFAULT;
				}
				else
					state = SECOND;
			}
			break;
		case SECOND:
			printf("Enter output filename: ");
			getstr(input, MAXLINE);
			trim(input);
			if (str_cmp(input, "") == 0) {
				printf("You must input a filename.");
				state = DEFAULT;
			} else {
				if ((fout = fopen(input, "wt")) == NULL) {
					printf("Sorry couldn't open file: %s\n",
						input);
					state = DEFAULT;
				}
				else
					state = CONVERT;
			}
			break;
		case CONVERT:
			puts("Converting file...");
			while (fgets(input, MAXLINE-1, fin) != NULL) {
				leetconv(output, input);
				fputs(output, fout);
			}
			fclose(fout);
			fclose(fin);
			puts("File written successfully...");
			state = DEFAULT;
			break;
		default:
			printf("What do you wish to do?\n"
				"1.  Convert from Keyboard.\n"
				"2.  Convert from file.\n"
				"3.  Exit\n\n"
				"Enter Option: ");
			getstr(input, MAXLINE);
			trim(input);
			answer = p_atoi(input);
			switch (answer) {
			case 1:
				printf("Enter some text: ");
				getstr(input, MAXLINE);
				trim(input);
				if (str_cmp(input, "") == 0)
					printf("You need to enter some"
						" text.\n");
				else {
					leetconv(output, input);
					printf("%s\n", output);
				}
				break;
			case 2:
				state = FIRST;
				break;
			case 3:
				printf("Quitting program...\n");
				answer = 0;
				break;
			default:
				break;
			}
		}
	} while (answer);

	return 0;
}
