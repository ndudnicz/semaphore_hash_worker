
#ifndef DEBUG_H
#define DEBUG_H
#include "worker.h"
void	print_config(t_shm_config *config);
void	print(char *str);
void	print_results(t_shm_config *config);

typedef struct	s_result
{
	pid_t		pid;
	int			solved;
}				t_result;
#endif //DEBUG_H
