#include "../common/helper.h"

int main()
{
	char s[] = "test case\n";
	char a[13];

	/* reverse_r test */
	trim(s);
	printf("Forwards: %s\n", s);
	reverse_r(s);
	printf("Backwards: %s\n", s);

	/* itoa_r test */
	itoa_r(1337, a);
	printf("%s\n", a);
	itoa_r(-1337, a);
	printf("%s\n", a);
	return 0;
}
