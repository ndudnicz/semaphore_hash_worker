#include "../includes/worker.h"
#include "../includes/debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: %s <worker_id>\n", av[0]);
		return (-1);
	}
	t_ipcs_config config = {0};
	config.worker_id = atoi(av[1]);

	int ret = init_ipcs(&config);
	if (ret == -1)
	{
		perror("Error initializing IPCS");
		return (-1);
	}
	// print_config(&config);
	ret = release_ipcs(&config);
	if (ret == -1)
	{
		perror("Error releasing IPCS");
		return (-1);
	}

}
