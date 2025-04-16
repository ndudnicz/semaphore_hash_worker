#include "../includes/worker.h"
#include "../includes/rand.h"
#include "../includes/debug.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int		get_board_addr(t_ipcs_config *config)
{
  	print("get_board_addr\n");
	print_config(config);
	config->board = (t_board*)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, config->shm_fd, 0);
	if (config->board == MAP_FAILED)
	{
		perror("Error mapping shared memory");
		return (-1);
	}
	return (0);
}

int		fill_board(t_ipcs_config *config)
{
	print("fill_board\n");
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		config->board->board_elements[i].value = generate_random_ulong();
		config->board->board_elements[i].solved = 0;
		config->board->board_elements[i].solver_id = 0;
		config->board->board_elements[i].nonce = 0;
		config->board->board_elements[i].hash = 0;
	}
	return (0);
}

int		init_shm(t_ipcs_config *config)
{
  print("init_ipcs\n");
	// check if the semaphore already exists
	config->shm_fd = shm_open(SHM_NAME, SHM_FLAG_FIRST, SHM_PERM);
    printf("first: %s(%d)\n", config->shm_fd == -1 ? "no" : "yes", config->shm_fd);
	if (config->shm_fd != -1)
	{
		get_board_addr(config);
		return (0);
	}
	config->shm_fd = shm_open(SHM_NAME, SHM_FLAG, SHM_PERM);

		int trunc_ret = ftruncate(config->shm_fd, SHM_SIZE);
		if (trunc_ret == -1)
		{
			perror("Error creating shared memory");
			return (-1);
		}
		get_board_addr(config);
	return 0;
		// return (fill_board(config));
}

int		release_shm(t_ipcs_config *config)
{
	if (shm_unlink(SHM_NAME) == -1)
	{
		perror("Error unlinking shared memory");
		return (-1);
	}
	return (0);
}