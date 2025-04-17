#include "../includes/worker.h"
#include <sys/mman.h>
#include <stdio.h>
int	main(void)
{
	if (shm_unlink(SHM_NAME) == -1)
	{
		perror("Error unlinking shared memory");
		return (-1);
	}
}