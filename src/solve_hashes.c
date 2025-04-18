#include "../includes/worker.h"
#include "../includes/rand.h"
#include "../includes/hash.h"
#include "../includes/benchmark.h"

#include <stdlib.h>
#include <stdio.h>

int		all_hashes_solved(t_shm_config *config)
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		if (config->board->board_elements[i].solved == 0)
			return (0);
	}
	return (1);
}

int		solve_hashes(t_shm_config *config)
{
	while(!all_hashes_solved(config))
	{
    	int random_i = arc4random_uniform(BOARD_SIZE);
        if (config->board->board_elements[random_i].solved == 0)
        {
        	printf("Worker %d: Solving hash for value %lu\n", config->worker_pid, config->board->board_elements[random_i].value);
        	unsigned int new_hash = 0;
        	unsigned int nonce = 0;
			start_bench();
            while (HASH_VALIDATE(new_hash) == 0)
            {
            	nonce = get_random_nonce_uint();
                if (config->debug == 1)
               	{
                	printf("Worker %d: Trying nonce %u for value %lu\n", config->worker_pid, nonce,
						 config->board->board_elements[random_i].value);
                }

            	new_hash = simple_hash_ulong(config->board->board_elements[random_i].value + nonce);
            	if (config->board->board_elements[random_i].solved == 1)
            	{
            		// it has been solved by another worker
            		break;
            	}
           	}
            float	elapsed_time = end_bench();
            if (config->board->board_elements[random_i].solved == 1)
            {
              	// it has been solved by another worker
            	continue;
            }
            printf("Worker %d: Found nonce %u for value %lu, hash(%lu): 0x%08X (%u) in %f seconds\n",
                   config->worker_pid, nonce,
                   config->board->board_elements[random_i].value,
                   config->board->board_elements[random_i].value + nonce,
                   new_hash, new_hash, elapsed_time);
			config->board->board_elements[random_i].nonce = nonce;
			config->board->board_elements[random_i].solved = 1;
			config->board->board_elements[random_i].solver_id = config->worker_pid;
            config->board->board_elements[random_i].hash = new_hash;
        }
	}
    return (0);
}