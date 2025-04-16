#include <stdio.h>
#include "../includes/worker.h"
#include <unistd.h>
#include <string.h>

void print_config(t_ipcs_config *config)
{
    printf("Worker ID: %d\n", config->worker_pid);
    printf("Shared Memory File Descriptor: %d\n", config->shm_fd);
    if (config->board == NULL)
	{
		printf("Board: NULL (not initialized)\n");
		return;
	}
        else {
	printf("Board: %x\n", config->board);
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		printf("Board element %d: value=%lu, solved=%d, solver_id=%d, nonce=%d, hash=%d\n",
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
