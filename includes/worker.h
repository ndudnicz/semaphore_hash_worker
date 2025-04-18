#ifndef WORKER_H
# define WORKER_H

# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/msg.h>
#include <fcntl.h>

# define BOARD_SIZE 200

typedef struct	s_board_element
{
	unsigned long	value;
	int				solved;
	int				solver_id;
	unsigned int	nonce;
	unsigned int	hash;
}				t_board_element;

typedef struct	s_board
{
	t_board_element	board_elements[BOARD_SIZE];
}				t_board;

# define IPCS_KEY	0x42424243
# define SHM_NAME "/my_shm"

# define SHM_SIZE	(sizeof(t_board))
# define SHM_PERM	0666
# define SHM_FLAG	(O_CREAT | O_RDWR)
# define SHM_FLAG_FIRST	(O_CREAT | O_RDWR | O_EXCL)

typedef struct	s_shm_config
{
	int				debug;
	int				first;
	int				shm_fd;
	int				shm_id;
	int				sem_id;
	int				msg_id;
	t_board			*board;
	pid_t			worker_pid;
}				t_shm_config;

int		init_shm(t_shm_config *config);
int		fill_board(t_shm_config *config);
int		release_shm(t_shm_config *config);
int		unmap_shm(t_shm_config *config);
int		solve_hashes(t_shm_config *config);

#endif //WORKER_H
