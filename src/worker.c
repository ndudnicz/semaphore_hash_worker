#include "../includes/worker.h"
#include "../includes/debug.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

int		main(int ac, char **av)
{
	t_shm_config config = {0};
	config.worker_pid = getpid();
	if (ac == 2 && av[1][0] == '-' && av[1][1] == 'd')
	{
		config.debug = 1;
	}
	else if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h')
    {
		printf("usage: ./worker [-d] [-h]\n");
		return (0);
    }

	init_shm(&config);
	print_config(&config);
	solve_hashes(&config);

	if (config.first == 1)
	{
		print_results(&config);
	}

	if (munmap(&config.board, BOARD_SIZE) == 0)
	{
		perror("munmap error");
	}

	if (config.first == 1 && shm_unlink(SHM_NAME) == -1)
	{
		perror("Error unlinking shared memory");
		return (-1);
	}
}
