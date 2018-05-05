#include "../common/bitmap.h"
#include <time.h>

int main(void)
{
	BITMAP_FILE *bmp;

	srand(time(NULL));
	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;
	make_BMP(bmp);
	write_BMP(bmp, 0);
	destroy_BMP(bmp);
	return 0;
}
