#include "../common/helper.h"

int main()
{
	int a[] = {9,8,7,6,5,4,3,2,1,0};
	int i;

	p_qsort(a, 0, 9);
	for (i = 0; i < 10; i++)
		printf("%d ", a[i]);
	putchar('\n');
	return 0;
}
