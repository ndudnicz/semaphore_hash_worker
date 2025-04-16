#include "../includes/worker.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "../includes/debug.h"

int		main(int ac, char **av)
{
	t_ipcs_config config = {0};
	config.worker_pid = getpid();

	int init_ret = init_shm(&config);
	if (init_ret == -1)
	{
		release_shm(&config);
		return (-1);
	}
	// print_config(&config);
	release_shm(&config);
}
