#include "../common/bitmap.h"
#include <time.h>

#define MAXLINE 256

int main(void)
{
	BITMAP_FILE *bmp;
	char line[MAXLINE];
	int i;

	srand(time(0));

	get_input("How many lines? ", line, MAXLINE);
	bmp = create_BMP("test.bmp", 64, 64, 24);
	if (!bmp)
		return 1;

	clear_BMP(bmp, 0, 0, 0);
	for (i = 0; i < p_atoi(line); i++) {
		int j = rand()%63;
		int k = rand()%63;
		int l = (j < 30) ? rand()%30+30 : rand()%30;
		int m = (k < 30) ? rand()%30+30 : rand()%30;
		draw_line_BMP(bmp, j, k, l, m,
			rand()%255, rand()%255, rand()%255);
	}
	write_BMP(bmp, 0);
	destroy_BMP(bmp);
	return 0;
}
