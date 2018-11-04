#include<stdio.h>

int main()
{
	long int a = -8999999;
	unsigned long long b = a;
	long c = b;
	printf("%ull\n", b);
	printf("%ld\n", (long)b);
	printf("%ld\n", c);
	printf("%ull", (unsigned long long)c);
	return 0;

}