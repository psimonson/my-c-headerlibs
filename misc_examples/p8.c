#include <stdio.h>

unsigned int getbit(unsigned int var, int bit);
unsigned int getbits(unsigned int var);

/* program to test my getbit function */
int main()
{
	int i;

	puts("Getting bit values...");
	for (i = 0; i < 16; i++)
		printf("Bit %d: %d\n", i, getbit(65535, i));
	printf("All bits: %d\n", getbits(32768));
	return 0;
}

unsigned int getbit(unsigned int var, int bit)
{
	return (var & 1 << bit);
}

unsigned int getbits(unsigned int var)
{
	return (var & ~(1<<0));
}
