#include <stdio.h>
#include "../includes/worker.h"
#include <unistd.h>
#include <string.h>
#include "../includes/debug.h"

void	print_config(t_shm_config *config)
{
    if (config->board == NULL)
	{
    	printf("{worker_id: %d, shm_fd: %d, first: %d, board_address : NULL ""}\n", config->worker_pid, config->shm_fd, config->first);
		return;
	}
    else {
    	printf("{ worker_id: %d, shm_fd: %d, first: %d, board_address : %p ""}\n",
                 config->worker_pid, config->shm_fd, config->first, config->board);
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		printf("Board element %d: value=%lu, solved=%d, solver_id=%d, nonce=%u, hash=0x%08X\n",
			   i, config->board->board_elements[i].value, config->board->board_elements[i].solved,
			   config->board->board_elements[i].solver_id, config->board->board_elements[i].nonce,
			   config->board->board_elements[i].hash);
	}
        }
}

void	print(char *str)
{
	write(1, str, strlen(str));
}

void	print_results(t_shm_config *config)
{
	t_result	results[200] = {0};
    int 		n_results = 0;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
      	int found = 0;
    	for (int j = 0; j < n_results; ++j)
    	{
    		if (results[j].pid == config->board->board_elements[i].solver_id)
    		{
    			results[j].solved++;
                found = 1;
    			break;
    		}
    	}
        if (found == 0)
        {
        	results[n_results].pid = config->board->board_elements[i].solver_id;
        	results[n_results].solved = 1;
        	n_results++;
        }
    }
    printf("Results:\n");
    for (int i = 0; i < n_results; ++i)
    {
    	printf("Worker %d solved %d hashes\n", results[i].pid, results[i].solved);
    }
}
