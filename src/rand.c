#include <stdlib.h>

unsigned long	generate_random_ulong(void)
{
	unsigned long high = (unsigned long)arc4random();
	unsigned long low  = (unsigned long)arc4random();

	return ((high << 16) | (low & 0xFFFF)) / 2 - 1; // Combine high and low bits
}

unsigned int	generate_random_uint(void)
{
	return arc4random() / 2 - 1;
}

unsigned int	get_random_nonce_uint(void)
{
	return arc4random() / 2 - 1;
}

unsigned long	get_random_nonce_ulong(void)
{
	return (unsigned long)arc4random() / 2 - 1;
}