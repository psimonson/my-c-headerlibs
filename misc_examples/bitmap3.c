#include "../common/bitmap.h"

int main(void)
{
	BITMAP_FILE *bmp;

	/* Load a bitmap named test.bmp */
	bmp = load_BMP("test.bmp");
	if (!bmp)		/* check for loading error */
		return 1;

	/* TODO: Add code here for bitmap */

	destroy_BMP(bmp);	/* free bmp resources */
	return 0;		/* return success */
}
