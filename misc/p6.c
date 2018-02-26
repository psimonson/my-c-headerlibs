#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define LOG_ERROR "[ERROR] : "
#define LOG_DEBUG "[DEBUG] : "

#define IN	1	/* inside a word */
#define OUT	0	/* outside a word */

struct _MAIN {
	FILE *fin;
	FILE *fout;
	long size;
};
typedef struct _MAIN main_t;

/* function to sort a file removing duplicate entries */
main_t startup(const char *name);
void cleanup(main_t *m);
int die(int, const char*, ...);
int tok_input(FILE*);
int sort_file(const main_t *m);

/* program to sort through a text file comparing words
 * removes duplicates.
 */
int main(int argc, char *argv[])
{
	main_t m;

	if (argc != 2)
		die(0, "Usage: %s <outfile.ext>\n"
				"Note: You can redirect input files into\n"
				"this program.\n", argv[0]);

	m = startup(argv[1]);
	tok_input(m.fin);
	m.size = ftell(m.fin);
	rewind(m.fin);
	printf("Processing input.");
	sort_file(&m);
	remove("data.tmp");
	cleanup(&m);
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

main_t startup(const char *n)
{
	main_t m;
	memset(&m, 0, sizeof(main_t));
	if ((m.fin = fopen("data.tmp", "w+t")) == NULL)
		die(1, LOG_ERROR "Cannot open file for reading/writing.\n");
	if ((m.fout = fopen(n, "w+t")) == NULL)
		die(1, LOG_ERROR "Cannot open file for reading/writing.\n");
	return m;
}

void cleanup(main_t *m)
{
	if (m->fin) fclose(m->fin);
	if (m->fout) fclose(m->fout);
	printf("done\n");
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

int sort_file(const main_t *m)
{
	char s[MAXSIZ];
	char s2[MAXSIZ];
	char f, i, res;
	const long siz = m->size/100;

	memset(s, 0, sizeof s);
	memset(s2, 0, sizeof s2);
	while ((res = getln_file(s, MAXSIZ-1, m->fin)) > 1 && res != EOF)
		if (strcmp(s, "") != 0 || strcmp(s, "\n") != 0) {
			fprintf(m->fout, "%s\n", s);
			break;
		}
	memset(s, 0, sizeof s);
	rewind(m->fout);
	rewind(m->fin);

	i = res = 0;
	while (1) {
		f = 0;
		if ((res = getln_file(s, MAXSIZ-1, m->fin)) == EOF)
			break;
		else if(res > 1) {
			while (1) {
				memset(s2, 0, sizeof s2);
				if (getln_file(s2, MAXSIZ-1, m->fout) == EOF)
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
				fseek(m->fout, 0, SEEK_END);
				fprintf(m->fout, "%s\n", s);
			}
			memset(s, 0, sizeof s);
			rewind(m->fout);
			if (siz*i <= m->size) {
				putchar('.');
				++i;
			}
		}
	}
	return 0;
}
