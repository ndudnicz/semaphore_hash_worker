#include <stdlib.h>

unsigned long generate_random_ulong(void)
{
	unsigned long high = (unsigned long)rand();
	unsigned long low  = (unsigned long)rand();

	return (high << 16) | (low & 0xFFFF); // Combine high and low bits
}