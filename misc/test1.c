#include "../common/logger.h"

#define LOG_NAME "log1.txt"

const char key[] = "N*(JdjOSIDU*U(*&#$(JFL";

int main(int argc, char *argv[])
{
	do_log(append_log, LOG_NAME, "Hello world!\n");
	do_log2(read_log, LOG_NAME);
	do_log2(crypt_log, LOG_NAME);
	return 0;
}
