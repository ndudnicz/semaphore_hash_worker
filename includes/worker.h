#ifndef WORKER_H
# define WORKER_H

# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/msg.h>

typedef struct	s_board_element
{
	unsigned long	value;
	int				solved;
	int				solver_id;
	int				nonce;
	int				hash;
}				t_board_element;

# define IPCS_KEY	0x42424243

# define BOARD_SIZE 10

# define SHM_SIZE	(sizeof(t_board_element) * BOARD_SIZE)
# define SHM_PERM	0666
# define SHM_FLAG	(IPC_CREAT | SHM_PERM)
# define SHM_FLAG_FIRST	(IPC_CREAT | IPC_EXCL | SHM_PERM)

# define SEM_PERM	0666
# define SEM_FLAG	(IPC_CREAT | IPC_EXCL | SEM_PERM)

# define MSG_PERM	0666
# define MSG_FLAG	(IPC_CREAT | IPC_EXCL | MSG_PERM)

typedef struct	s_ipcs_config
{
	int				shm_id;
	int				sem_id;
	int				msg_id;
	t_board_element	*board[BOARD_SIZE];
	int				worker_id;
}				t_ipcs_config;

int		init_ipcs(t_ipcs_config *config);
int		release_ipcs(t_ipcs_config *config);

#endif //WORKER_H
