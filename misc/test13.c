#include "../common/prs_string.h"
#include <string.h>
#include <dirent.h>

#define MAXDIR 1024

char dir[MAXDIR];

/* program to test my find function */
int main(int argc, char *argv[])
{
	int find(void);

	return find();
}

/* find:  allows to append to end of current directory */
int find(void)
{
	extern int getcwd(char *s, size_t size);
	char buf[BUFSIZ];
	DIR *d;

	get_input("Enter a directory: ", buf, BUFSIZ);
	getcwd(dir, MAXDIR);
	strncat(dir, "/", 1);
	strncat(dir, buf, strlen(buf));
	printf("You entered: %s\nCurrent Directory: %s\n",
		buf, dir);
	d = opendir(dir);
	if (d == NULL) {
		printf("Directory doesn't exist.\n");
		return 1;
	}
	closedir(d);
	printf("Directory exists!\n");
	return 0;
}
