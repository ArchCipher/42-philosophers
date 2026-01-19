#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define E_ARGS1 "number_of_philosophers time_to_die time_to_eat time_to_sleep"
# define E_ARGS2 "[number_of_times_each_philosopher_must_eat]"
# define E_INVAL "Invalid argument"
# define E_NOMEM "Out of memory"
# define E_AGAIN "Resource temporarily unavailable"
# define E_PERM "Operation not permitted"
# define E_DEADLK "Resource deadlock avoided"
# define E_SRCH "No such process"
# define E_FAULT "Bad address"
# define E_NOTRECOVERABLE "State not recoverable"
# define E_OWNERDEAD "Owner died"
# define E_BUSY "Device or resource busy"

# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEATH "died"

# define CREATE "pthread_create"
# define JOIN "pthread_join"

# define INIT "pthread_mutex_init"
# define DESTROY "pthread_mutex_destroy"
# define LOCK "pthread_mutex_lock"
# define UNLOCK "pthread_mutex_unlock"

typedef enum e_mutex_op
{
	MUTEX_INIT,
	MUTEX_DESTROY,
	MUTEX_LOCK,
	MUTEX_UNLOCK
}			t_mutex_op;

typedef struct s_input
{
	int				philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long long		sim_start;
	int				sim_stop;
	pthread_t		*thread_ids;
	pthread_mutex_t	*forks;
	pthread_mutex_t	global_state;
}					t_input;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	state;
	t_input			*input;
}					t_philo;

int	parse_input(char **av, t_input *input);

int	mutex_op(pthread_mutex_t *mutex, t_mutex_op op, const char *name);
int init_philo(t_input *input, t_philo *philos);
// t_philo *init_philo(t_input *input);

int	create_manage_threads(t_input *input, t_philo *philos);
// int create_manage_threads(t_input *input, t_philo *philos);
void destroy_mutex(pthread_mutex_t *mutex);
void	destroy_mutexes(t_input *input, t_philo *philos, int end);

void	*run_sim(void *arg);
void	*monitor_sim(void *arg);

void	stop_simulation(t_input *input);

void	precise_sleep(long long millisec);

long long			get_time(void);
int	read_int(pthread_mutex_t *state, int *data);
int	should_stop_sim(t_input *input);
void	sim_print(t_philo *philo, const char *action, bool is_death);

void	perr(const char *function, int errnum);

#endif
