#include "../includes/worker.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "../includes/debug.h"

int		main(void)
{
	t_shm_config config = {0};
	config.worker_pid = getpid();
	config.first = 0;
	init_shm(&config);
	print_config(&config);
	solve_hashes(&config);

	if (config.first == 1)
	{
		print_config(&config);
	}

	if (config.first == 1 && shm_unlink(SHM_NAME) == -1)
	{
		perror("Error unlinking shared memory");
		return (-1);
	}
}
