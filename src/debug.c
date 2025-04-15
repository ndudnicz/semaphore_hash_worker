#include <stdio.h>
#include "../includes/worker.h"
#include <unistd.h>
#include <string.h>

void print_config(t_ipcs_config *config)
{
  	printf("Shared Memory ID: %d\n", config->shm_id);
    printf("Semaphore ID: %d\n", config->sem_id);
    printf("Message Queue ID: %d\n", config->msg_id);
    printf("Worker ID: %d\n", config->worker_id);
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
			   i, config->board[i]->value, config->board[i]->solved,
			   config->board[i]->solver_id, config->board[i]->nonce,
			   config->board[i]->hash);
	}
        }
}

void print(char *str)
{
	write(1, str, strlen(str));
}
