/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:04:07 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/22 22:24:14 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define PROG "philo"

// error messages
# define E_ARGS1 "number_of_philosophers time_to_die time_to_eat time_to_sleep"
# define E_ARGS2 "[number_of_times_each_philosopher_must_eat]"

// actions
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEATH "died"

// thread and mutex function names
# define CREATE "pthread_create"
# define JOIN "pthread_join"
# define INIT "pthread_mutex_init"
# define DESTROY "pthread_mutex_destroy"
# define LOCK "pthread_mutex_lock"
# define UNLOCK "pthread_mutex_unlock"

typedef struct s_err
{
	int				code;
	const char		*msg;
}					t_err;

typedef enum e_mutex_op
{
	MUTEX_INIT,
	MUTEX_DESTROY,
	MUTEX_LOCK,
	MUTEX_UNLOCK
}					t_mutex_op;

typedef struct s_input
{
	int				philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long long		sim_start;
	int				sim_done;
	pthread_t		*thread_ids;
	int				threads_ready;
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

void				cleanup(t_input *input, t_philo *philos);
int					parse_input(char **av, t_input *input);

int					init_philo(t_input *input, t_philo *philos);
int					mutex_op(pthread_mutex_t *mutex, t_mutex_op op,
						const char *name);
void				destroy_mutexes(t_input *input, t_philo *philos, int end);

int					create_manage_threads(t_input *input, t_philo *philos);
void				*run_sim(void *arg);
void				run_routine(t_philo *philo);
void				*monitor_sim(void *arg);
void				stop_sim(t_input *input);

long long			get_time(bool usec);
void				sim_print(t_philo *philo, const char *msg1,
						const char *msg2, bool is_death);
int					read_int(pthread_mutex_t *state, int *data);
int					sim_done(t_input *input);
void				precise_sleep(long long usec);

void				perr(const char *name, int errnum);

#endif
