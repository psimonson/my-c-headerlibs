#include "../common/helper.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s <text-here>\n"
			"NOTE: Be sure to use double quotes around text.\n",
			argv[0]);
		return 0;
	}
	printf("Input: %s\n", argv[1]);
	reverse_r(argv[1]);
	printf("Output: %s\n", argv[1]);
	return 0;
}
