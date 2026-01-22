/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:07:27 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/22 22:21:18 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROG "philo_bonus"

// error messages
# define E_ARGS1 "number_of_philosophers time_to_die time_to_eat time_to_sleep"
# define E_ARGS2 "[number_of_times_each_philosopher_must_eat]"

// actions
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEATH "died"

// semaphore and thread function names
# define OPEN "sem_open"
# define WAIT "sem_wait"
# define POST "sem_post"

# define CREATE "pthread_create"
# define JOIN "pthread_join"

# define SIG_EXIT_BASE 128

typedef struct s_err
{
	int			code;
	const char	*msg;
}				t_err;

typedef enum e_mutex_op
{
	MUTEX_INIT,
	MUTEX_DESTROY,
	MUTEX_LOCK,
	MUTEX_UNLOCK
}				t_mutex_op;

typedef struct s_input
{
	int			philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_must_eat;
	long long	sim_start;
	sem_t		*forks;
	sem_t		*print;
	pid_t		*pids;
}				t_input;

typedef struct s_philo
{
	int					id;
	_Atomic long long	last_meal_time;
	_Atomic int			meals_eaten;
	t_input				*input;
	pthread_t			thread_id;
}				t_philo;

int				parse_input(char **av, t_input *input);

int				init_sem(t_input *input);

void			run_sim(t_philo *philo);
void			*monitor_sim(void *arg);

long long		get_time_safe(bool usec);
long long		get_time(bool usec);
void			precise_sleep(long long usec);

void			error_exit_child(const char *name, int errnum);
void			perr(const char *name, int errnum);

#endif
