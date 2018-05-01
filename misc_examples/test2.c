#include "../common/helper.h"
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
			getstr(buf, sizeof buf);
			trim(buf);
			do_log(write_log, LOG_NAME, "%s\n", buf);
			do_log2(crypt_log, LOG_NAME);
		break;
		case 'a':
			do_log2(crypt_log, LOG_NAME);
			printf("INPUT >> ");
			getstr(buf, sizeof buf);
			trim(buf);
			do_log(append_log, LOG_NAME, "%s\n", buf);
			do_log2(crypt_log, LOG_NAME);
		break;
		case 'r':
			if (do_log2(crypt_log, LOG_NAME) < 0) {
				printf("Run 'w' or 'a' options first.\n"
					"Cannot read log, it doesn't"
					" exist.\n");
				return 1;
			}
			do_log2(read_log, LOG_NAME);
			do_log2(crypt_log, LOG_NAME);
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
