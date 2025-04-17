#include <stdio.h>
#include "../includes/worker.h"
#include <unistd.h>
#include <string.h>

void print_config(t_shm_config *config)
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

void print(char *str)
{
	write(1, str, strlen(str));
}
