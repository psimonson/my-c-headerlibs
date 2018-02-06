#include "../common/prs_string.h"
#include "../common/logger.h"

#define LOG_NAME "log2.txt"

const char key[] = "OSijf9f8w*f^*&%^^%$";

int main(int argc, char *argv[])
{
	char buf[BUFSIZ];

	if (argc == 1) {
		fprintf(stderr, "Usage: %s -war\n", argv[0]);
		return 1;
	}

	switch (argv[1][0]) {
	case '-':
		switch (argv[1][1]) {
		case 'w':
			printf("INPUT >> ");
			readln2(buf, sizeof buf);
			trim_string(buf);
			if (write_log(LOG_NAME, "%s\n", buf) < 0)
				return -1;
			crypt_log(NULL);
		break;
		case 'a':
			if (crypt_log(LOG_NAME) < 0) {
				printf("Use 'w' option first.\n");
				return -1;
			}
			printf("INPUT >> ");
			readln2(buf, sizeof buf);
			trim_string(buf);
			if (append_log(NULL, "%s\n", buf) < 0)
				return -1;
			if (crypt_log(NULL) < 0)
				return -1;
		break;
		case 'r':
			if (crypt_log(LOG_NAME) < 0) {
				printf("Use 'w' option first!\n");
				return -1;
			}
			if (read_log(NULL) < 0)
				return -1;
			if (crypt_log(NULL) < 0)
				return -1;
		break;
		default:
			printf("Unknown option '%c'\n", argv[1][1]);
		}
	break;
	default:
		printf("Unknown option '%c'\n", argv[1][0]);
		return 2;
	}
	return 0;
}
