#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// # define TAKE_FORK "has taken a fork"
// # define EAT "is eating"
// # define SLEEP "is sleeping"
// # define THINK "is thinking"
// # define DEATH "died"

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

typedef enum e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DEATH
}					t_action;

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

int init_philo(t_input *input, t_philo *philos);
// t_philo *init_philo(t_input *input);

int	create_manage_threads(t_input *input, t_philo *philos);
// int create_manage_threads(t_input *input, t_philo *philos);
void	stop_simulation(t_philo *philo);

void	*run_sim(void *arg);
void	*monitor_sim(void *arg);

long long			get_time(void);
long long			read_data(pthread_mutex_t *state, void *data);
int	should_stop_sim(t_input *input);
void				sim_print(t_philo *philo, int action);


const char			*ft_strerror(int errnum);
const char			*get_simaction_str(t_action act);

#endif
