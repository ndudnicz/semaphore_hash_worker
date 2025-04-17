#include <stdio.h>
#include <stdlib.h>

#include "../includes/hash.h"

int    main(int ac, char **av)
{
    if (ac != 2)
    {
        fprintf(stderr, "Usage: %s <number>\n", av[0]);
        return 1;
    }
    const unsigned long input = strtoul(av[1], NULL, 10);
    const unsigned int hash = simple_hash_ulong(input);

    printf("Hash of %lu is: 0x%4x (%u)\n", input, hash, hash);
    printf("Hash validate: %d\n", HASH_VALIDATE(hash));

    return 0;
}