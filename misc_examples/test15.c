#include "../common/helper.h"

int main()
{
	char msg[256];
	int len;

	printf("Send 'EOF' to quit. (Windows/Linux) [Ctrl+Z/Ctrl+D]\n");
	do {
		printf("Enter string: ");
		len = getstr(msg, sizeof msg);
		if (len > 1) {
			len = trim(msg);
			printf("Size: %d\nString: %s", len, msg);
		} else {
			if (msg[0] != '\n')
				putchar('\n');
			printf("Program has ended.\n");
		}
	} while(len > 1);
	return 0;
}
