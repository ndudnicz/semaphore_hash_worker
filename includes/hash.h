#ifndef HASH_H
# define HASH_H

# define INIT_HASH 0x19919 // prime number 104729
# define MIX_PRIME 0x5bd1e995
# define ITERATIONS 1000000 // slow down hash calculation
# define HASH_MASK 0xff000000
# define HASH_VALIDATE(X) ((X & HASH_MASK) == HASH_MASK)

unsigned int	simple_hash_ulong(unsigned long input);
unsigned short	simple_hash_uint(unsigned int input);

#endif //HASH_H
