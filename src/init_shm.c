#include "../includes/worker.h"
#include "../includes/rand.h"
#include "../includes/debug.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int		get_board_addr(t_shm_config *config)
{
  	print("get_board_addr\n");
	config->board = (t_board*)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, config->shm_fd, 0);
	if (config->board == MAP_FAILED)
	{
		perror("Error mapping shared memory");
		return (-1);
	}
	return (0);
}

int		fill_board(t_shm_config *config)
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
	return (1);
}

int		init_shm(t_shm_config *config)
{
	config->first = 1;
	config->shm_fd = shm_open(SHM_NAME, SHM_FLAG_FIRST, SHM_PERM);
	if (config->shm_fd == -1)
	{
		config->first = 0;
		print("Error : shm_fd == -1, getting fd again with normal flags\n");
		config->shm_fd = shm_open(SHM_NAME, SHM_FLAG, SHM_PERM);
	}

	if (config->first == 1)
	{
		int trunc_ret = ftruncate(config->shm_fd, SHM_SIZE);

		if (trunc_ret == -1)
		{
			perror("Error creating shared memory");
			 return (-1);
		}
	}

	get_board_addr(config);
	if (config->board == MAP_FAILED)
	{
		perror("Error mapping shared memory");
		 return (-1);
	}

	if (config->first == 1)
	{
		fill_board(config);
	}
    return (0);
}

int		unmap_shm(t_shm_config *config)
{
	if (config->board != NULL)
	{
		if (munmap(config->board, SHM_SIZE) == -1)
		{
			perror("Error unmapping shared memory");
			return (-1);
		}
		config->board = NULL;
	}
	return (0);
}

int		release_shm(t_shm_config *config)
{
	if (unmap_shm(config) == -1)
	{
		perror("Error unmapping shared memory");
		return (-1);
	}
	if (shm_unlink(SHM_NAME) == -1)
	{
		perror("Error unlinking shared memory");
		return (-1);
	}
	return (0);
}

