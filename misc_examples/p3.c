#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define LOG_ERROR "[ERROR] : "
#define LOG_DEBUG "[DEBUG] : "

#define IN	1	/* inside a word */
#define OUT	0	/* outside a word */

/* function to sort a file removing duplicate entries */
int die(int, const char*, ...);
int tok_input(FILE*);
int sort_file(FILE*, FILE*);

/* program to sort through a text file comparing words
 * removes duplicates.
 */
int main(int argc, char *argv[])
{
	FILE* fin;
	FILE* fout;

	if (argc != 2)
		die(0, "Usage: %s <outfile.ext>\n", argv[0]);

	if ((fout = fopen("data.tmp", "wt")) == NULL)
		die(1, LOG_ERROR "Cannot open file for writing.\n");
	tok_input(fout);
	fclose(fout);
	if ((fin = fopen("data.tmp", "rt")) == NULL)
		die(1, LOG_ERROR "Cannot open file for reading.\n");
	if ((fout = fopen(argv[1], "w+t")) == NULL)
		die(1, LOG_ERROR "Cannot open file for writing.\n");
	rewind(fin);
	sort_file(fin, fout);
	fclose(fin);
	fclose(fout);
	remove("data.tmp");
	puts("Done writing file...");
	return 0;
}

int die(int ret, const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);
	exit(ret);
}

int tok_input(FILE* fout)
{
	int c, state;
	state = OUT;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
			fputc('\n', fout);
		} else if (state == OUT)
			state = IN;
		if (!isalpha(c))
			continue;
		fputc(c, fout);
	}
	return 0;
}

#define MAXSIZ 128

int getln_file(char *s, int lim, FILE *f)
{
	int c, i;

	for (i = 0; i < lim-1 && (c = fgetc(f)) != EOF && c != '\n'; ++i)
		s[i] = c;
	s[i] = 0;
	if (c == EOF)
		return -1;
	return i;
}

int sort_file(FILE* fin, FILE* fout)
{
	char s[MAXSIZ];
	char s2[MAXSIZ];
	char f;

	memset(s, 0, sizeof s);
	memset(s2, 0, sizeof s2);
	getln_file(s, MAXSIZ-1, fin);
	fprintf(fout, "%s\n", s);
	memset(s, 0, sizeof s);
	rewind(fout);
	rewind(fin);

	while (1) {
		f = 0;
		if (getln_file(s, MAXSIZ-1, fin) == EOF)
			break;
		while (1) {
			memset(s2, 0, sizeof s2);
			if (getln_file(s2, MAXSIZ-1, fout) == EOF)
				break;
#if defined(DEBUG)
			printf("input: %s\t\toutput: %s\n",
					s, s2);
#endif
			if (strcmp(s, s2) == 0) {
				f = 1;
				break;
			}
		}
		if (!f) {
			fseek(fout, 0, SEEK_END);
			fprintf(fout, "%s\n", s);
		}
		memset(s, 0, sizeof s);
		rewind(fout);
	}
	return 0;
}
