#include "../includes/worker.h"
#include "../includes/rand.h"
#include "../includes/debug.h"
#include <stdio.h>

int		get_board_addr(t_ipcs_config *config)
{
  	print("get_board_addr\n");
	if ((config->board = shmat(config->shm_id, NULL, 0)) == (void*)-1)
		return (-1);
    printf("board: %x\n", config->board);
	return (0);
}

int		fill_board(t_ipcs_config *config)
{
	print("fill_board\n");
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		config->board[i]->value = generate_random_ulong();
		config->board[i]->solved = 0;
		config->board[i]->solver_id = 0;
		config->board[i]->nonce = 0;
		config->board[i]->hash = 0;
	}
	return (0);
}

int		init_ipcs(t_ipcs_config *config)
{
  print("init_ipcs\n");
	// check if the semaphore already exists
	const int first = shmget(IPCS_KEY, SHM_SIZE, SHM_FLAG_FIRST) == -1 ? 0 : 1;
    printf("first: %s(%d)\n", first == 0 ? "no" : "yes", first);
	if (first == 0)
	{
		if ((config->shm_id = shmget(IPCS_KEY, SHM_SIZE, SHM_PERM)) == -1)
			return -1;
		if ((config->sem_id = semget(IPCS_KEY, 1, SEM_PERM)) == -1)
			return -1;
		if ((config->msg_id = msgget(IPCS_KEY, MSG_PERM)) == -1)
			return -1;
        get_board_addr(config);
		return (0);
	}
	else
	{
		if ((config->shm_id = shmget(IPCS_KEY, SHM_SIZE, SHM_PERM)) == -1)
			return -1;
		if ((config->sem_id = semget(IPCS_KEY, 1, SEM_FLAG)) == -1)
			return -1;
		if ((config->msg_id = msgget(IPCS_KEY, MSG_FLAG)) == -1)
			return -1;
		semctl(config->sem_id, 0, SETVAL, 1);
        get_board_addr(config);
		return (fill_board(config));
	}
}

int		release_ipcs(t_ipcs_config *config)
{
  	print("release_ipcs\n");
	if (shmdt(config->board) == -1)
		return (-1);
        print("1\n");
	if (shmctl(config->shm_id, IPC_RMID, NULL) == -1)
		return (-1);
	print("2\n");

	if (semctl(config->sem_id, 0, IPC_RMID) == -1)
		return (-1);
	print("3\n");

	if (msgctl(config->msg_id, IPC_RMID, NULL) == -1)
		return (-1);
	print("4\n");

	return (0);
}