#include "../common/bitmap.h"

int main(void)
{
	if (create_BMP("hello_1337.bmp", 800, 600, 24) != 0) {
		fprintf(stderr, "Failed to create bitmap.\n");
		return 1;
	} else
		fprintf(stdout, "Bitmap create successfully.\n");
	return 0;
}
