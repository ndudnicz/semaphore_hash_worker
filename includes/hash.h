#ifndef HASH_H
# define HASH_H

# define INIT_HASH 0x19919 // prime number 104729
# define HASH_MASK 0xff00000
# define HASH_VALIDATE(X) ((X & HASH_MASK) == HASH_MASK)

unsigned int	simple_hash_ulong(unsigned long input);
unsigned short	simple_hash_uint(unsigned int input);

#endif //HASH_H
