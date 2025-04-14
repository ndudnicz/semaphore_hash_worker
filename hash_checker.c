#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

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

    unsigned long input = strtoul(av[1], NULL, 10);
    unsigned short hash = simple_hash(input);

    printf("Hash of %lu is: %2x\n", input, hash);

    return 0;
}