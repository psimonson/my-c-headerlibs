#include "my-c-headerlibs/common/helper.h"
#include "my-c-headerlibs/common/tempfile.h"

#define MAXLEN    256
#define MAXCHARS  26
#define MAXLINES  2048
#define MAXPATH   260

static char file_data[MAXCHARS] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static int file_data2[MAXLINES][MAXCHARS];

void process_file(FILE *fp)
{
	extern char file_data[];
	extern int file_data2[][MAXCHARS];
	char buf[MAXLEN], *p;
	int i,j;

	i = 0;
	while (fgets(buf, MAXLEN, fp) != NULL) {
		(void)trim(buf);
		p = &buf[0];
		/* iterate through characters of buffer */
		while (*p != 0) {
			/* iterate through characters in file_data */
			for (j=0; j < MAXCHARS; j++)
				if (toupper(*p) == file_data[j])
					file_data2[i][j]++;
			p++;
		}
		i++;
	}
}

void rewrite_file(FILE *fp, const char *filename)
{
	extern char file_data[];
	extern int file_data2[][MAXCHARS];
	char buf[MAXLEN];
	FILE *tmp;
	int i,j;

	tmp = tempfile();
	if (!tmp)
		return;

	i = 0;
	while (fgets(buf, MAXLEN, fp) != NULL) {
		(void)trim(buf);
		fprintf(tmp, "%s ", buf);
		for (j=0; j < MAXCHARS-1; j++)
			fprintf(tmp, "%d ", file_data2[i][j]);
		fprintf(tmp, "%d\n", file_data2[i][MAXCHARS-1]);
		i++;
	}
	rewind(tmp);
	if ((fp = freopen(filename, "wt", fp)) == NULL) {
		fprintf(stderr, "Error: Cannot open file %s for writing.\n",
			filename);
		return;
	}
	while (fgets(buf, MAXLEN, tmp) != NULL) {
		fputs(buf, fp);
	}
	fclose(tmp);
}

int main(void)
{
	char buf[MAXLEN];
	char filename[MAXPATH];
	FILE *fp;

	(void)get_input("Enter filename: ", buf, MAXLEN);
	(void)trim(buf);
	str_cpy(filename, buf);

	if ((fp = fopen(buf, "rt")) == NULL) {
		fprintf(stderr, "Error: Cannot open file %s for reading.\n",
			buf);
		return 1;
	}
	process_file(fp);
	rewind(fp);
	rewrite_file(fp, filename);
	fclose(fp);
	printf("Done reading file...\n");
	return 0;
}
