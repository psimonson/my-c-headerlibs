#include "../common/logger.h"
#include "../common/tempfile.h"

#define LOG_NAME	"log3.txt"

const char key[] = "LKASLsdj#*&%@&$@*#&$";

/* test functions */
int test1(void);
int test2(void);
int test3(void);

/* run tests listed inside */
int run_tests(int (*[])(void));

/* test count */
int (*tests[])(void) = {
	test1,
	test2,
	test3
};
#define TOTAL_TESTS ((int)sizeof(tests)/sizeof(int (*)(void)))

int main(int argc, char *argv[])
{
	int passed;

	if (argc == 1) {
		do_log(write_log, LOG_NAME, "Running File Operation Tests...\n");
		passed = run_tests(tests);
		printf("Tests passed: %d/%u\n", passed, TOTAL_TESTS);
		do_log(append_log, LOG_NAME, "Tests passed: %d/%u\n", passed, TOTAL_TESTS);
		if (passed == 0) {
			printf("All tests failed!\n");
		} else {
			if (passed == TOTAL_TESTS) {
				printf("All tests passed!\n");
			} else {
				printf("Some tests passed!\n");
			}
		}
		do_log2(crypt_log, LOG_NAME);
	} else if (argc == 2 && (argv[1][0] == '-' && argv[1][1] == 'r')) {
		do_log2(crypt_log, LOG_NAME);
		do_log2(read_log, LOG_NAME);
		do_log2(crypt_log, LOG_NAME);
	} else {
		fprintf(stderr, "Usage: %s [-r]\n", argv[0]);
		return 1;
	}
	return 0;
}

int run_tests(int (*func[])(void))
{
	int passed;
	int i;
	passed = 0;
	for (i = 0; i < TOTAL_TESTS; i++)
		passed += func[i]();
	return passed;
}

int test1(void)
{
	FILE *fp = tempfile();
	if (fp == NULL)
		return 0;

	do_log(append_log, LOG_NAME, "Test 1 : Succeeded!\n");
	return 1;
}

int test2(void)
{
	if (fclose(__tempfile) == 0) {
		__tempfile = NULL;
		do_log(append_log, LOG_NAME, "Test 2 : Succeeded!\n");
		return 1;
	}
	return 0;
}

/* test3:  create log file but don't close it */
int test3(void)
{
	FILE *fp;
	if ((fp = tempfile()) == NULL) {
		do_log(append_log, LOG_NAME, "Test 3 : Failed!\n");
		return 0;
	}
	do_log(append_log, LOG_NAME, "Test 3 : Succeeded!\n");
	return 1;
}

