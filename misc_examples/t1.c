#include "../common/helper.h"

#define MAXLINE 512

int main()
{
	char s1[MAXLINE];
	char s2[MAXLINE];
	char s3[MAXLINE];

	/* testing getline function */
	printf("Enter a string to reverse: ");
	getstr(s1, MAXLINE);
	/* reverse functions testing */
	printf("======================\n"
		"String reversing\n"
		"======================\n");
	reverse(s1);
	printf("Backward: %s\n", s1);
	reverse_r(s1);
	printf("Forward: %s\n", s1);

	/* alphasort testing */
	printf("Enter a string to sort: ");
	getstr(s2, MAXLINE);
	printf("=====================\n"
		"Alpha sort - below...\n"
		"=====================\n");
	reverse_r(s2);
	printf("Before: %s\n", s2);
	alpha_sort(s2, str_len(s2));
	printf("After: %s\n", s2);

	/* testing atoi */
	printf("======================\n"
		"Testing ATOI function\n"
		"======================\n");
	printf("Before: 51298\n"
		"After: %d\n", p_atoi("51298"));

	/* testing strcmp */
	printf("Enter first string to compare: ");
	getstr(s2, MAXLINE);
	printf("Enter second string to compare: ");
	getstr(s3, MAXLINE);
	printf("======================\n"
		"Testing STRCMP Function\n"
		"======================\n");
	printf("String compare: %s - %s\n", s2, s2);
	printf("Result: %s\n", (str_cmp(s2, s2) == 0) ? "True" : "False");
	printf("String compare: %s - %s\n", s2, s3);
	printf("Result: %s\n", (str_cmp(s2, s3) == 0) ? "True" : "False");
	return 0;
}
