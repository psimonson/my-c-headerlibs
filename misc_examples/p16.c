#include "../common/helper.h"

#define MAXBUF 1024

int search_file(FILE *, const char *);
int search_line(const char *, const char *);

/* program to search files for a given string */
int main(int argc, char *argv[])
{
	char buf[BUFSIZ];
	FILE *fp;
	int res;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename.ext>\n", argv[0]);
		return 1;
	}

	mem_set(buf, 0, sizeof buf);
	(void)get_input("What to search for: ", buf, sizeof buf);
	trim(buf);
	if ((fp = fopen(argv[1], "rt")) == NULL) {
		fprintf(stderr, "Error: Cannot open file for reading.\n");
		return 2;
	}
	res = search_file(fp, buf);
	printf("Found: %s\n", (res == 1) ? "True" : "False");
	fclose(fp);

	return 0;
}

/* search_file:  search for s in file (fp) */
int search_file(FILE *fp, const char *buf)
{
	char line[MAXBUF];
	int res;

	res = 0;
	while (fgets(line, sizeof line, fp) != NULL)
		res = search_line(line, buf);
	return res;
}

/* search_line:  search for t in s */
int search_line(const char *s, const char *t)
{
	while (*s != *t)
		s++;
	return (str_cmp(s, t) != 0);
}
