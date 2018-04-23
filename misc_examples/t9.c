#include "../common/helper.h"

/* program to test my swap macro */
int main(void)
{
	int a = 12;
	int b = 14;
	char t[2] = {1,2};

	/* swap a and b */
	printf("a: %d\tb: %d\n", a, b);
	SWAP(int, a, b);
	printf("a: %d\tb: %d\n", a, b);
	/* swap t[1] and t[2] */
	printf("t[0]: %d\tt[1]: %d\n", t[0], t[1]);
	SWAP(char, t[0], t[1]);
	printf("t[0]: %d\tt[1]: %d\n", t[0], t[1]);
	return (a - b + t[1]) == t[0]; /* should equal 0 */
}
