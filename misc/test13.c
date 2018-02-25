#include "../common/prs_string.h"
#include <string.h>
#include <dirent.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#define MAXDIR 1024

char dir[MAXDIR];

/* program to test my find function */
int main(int argc, char *argv[])
{
	int find_directory(void);
	int find_file(void);

	if (argc > 2) {
		printf("Usage: %s [-f]\n", argv[0]);
		return 1;
	}

	if (argc == 1)
		return find_directory();
	else if (argc == 2 && argv[1][0] == '-') {
		while(*++argv[1]) {
			switch (*argv[1]) {
			case 'f':
				return find_file();
			break;
			default:
				printf("Unknown option '%c'.\n", *argv[1]);
			}
		}
	}
	return 2;
}

/* find:  allows to append to end of current directory */
int find_directory(void)
{
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

int find_file(void)
{
	char buf[BUFSIZ];

	get_input("Enter a filename: ", buf, BUFSIZ);
	getcwd(dir, MAXDIR);
	strncat(dir, "/", 1);
	strncat(dir, buf, strlen(buf));
	printf("You entered: %s\nCurrent Filename: %s\n",
		buf, dir);
#ifdef _WIN32
	if (_access(dir, 0) < 0) {
		if (errno == EEXIST)
			printf("File doesn't exist.\n");
		else
			printf("Error occurred trying to access file.\n");
		return 1;
	}
#else
	if (access(dir, 0) < 0) {
		if (errno == EEXIST)
			printf("File doesn't exist.\n");
		else
			printf("Error occurred trying to access file.\n");
		return 1;
	}
#endif
	printf("File exists.\n");
	return 0;
}
