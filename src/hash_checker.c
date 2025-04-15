#include <stdio.h>
#include <stdlib.h>

#include "../includes/hash.h"

int    main(int ac, char **av)
{
    for (int i = 0; i < ac; ++i)
    {
        printf("Argument %d: %s\n", i, av[i]);
    }
    if (ac != 2)
    {
        printf("Usage: %s <number>\n", av[0]);
        return 1;
    }

    const unsigned long input = strtoul(av[1], NULL, 10);
    const unsigned int hash = simple_hash(input);

    printf("Hash of %lu is: 0x%4x(%hd)\n", input, hash, hash);

    return 0;
}