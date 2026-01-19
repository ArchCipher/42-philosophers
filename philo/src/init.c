/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:47:42 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/18 20:57:30 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_input *input, t_philo *philos);
static void	init_threads(t_input *input, t_philo *philos);

int	init_philo(t_input *input, t_philo *philos)
{
	input->forks = malloc(sizeof(pthread_mutex_t) * input->philos);
	if (!input->forks)
		return (perr("malloc", errno), 1);
	if (init_mutexes(input, philos))
		return (free(input->forks), 1);
	input->thread_ids = malloc(sizeof(pthread_t) * (input->philos + 1));
	if (!input->thread_ids)
		return (perr("malloc", errno), free(input->forks), 1);
	input->sim_start = get_time();
	if (input->sim_start < 0)
		return (free(input->forks), free(input->thread_ids), 1);
	init_threads(input, philos);
	return (0);
}

static int	init_mutexes(t_input *input, t_philo *philos)
{
	int	i;

	if (mutex_op(&input->global_state, MUTEX_INIT, INIT))
		return (1);
	i = 0;
	while (i < input->philos)
	{
		if (mutex_op(input->forks + i, MUTEX_INIT, INIT))
		{
			destroy_mutexes(input, philos, i);
			return (1);
		}
		if (mutex_op(&philos[i].state, MUTEX_INIT, INIT))
		{
			mutex_op(input->forks + i, MUTEX_DESTROY, DESTROY);
			destroy_mutexes(input, philos, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	init_threads(t_input *input, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < input->philos)
	{
		philos[i].id = i + 1;
		philos[i].first_fork = input->forks + ((i + 1) % input->philos);
		philos[i].second_fork = input->forks + i;
		if (philos[i].id % 2 == 0)
		{
			philos[i].first_fork = input->forks + i;
			philos[i].second_fork = input->forks + ((i + 1) % input->philos);
		}
		philos[i].last_meal_time = input->sim_start;
		philos[i].meals_eaten = 0;
		philos[i].input = input;
		i++;
	}
}

int	mutex_op(pthread_mutex_t *mutex, t_mutex_op op, const char *name)
{
	int	err;

	err = 0;
	if (op == MUTEX_INIT)
		err = pthread_mutex_init(mutex, NULL);
	else if (op == MUTEX_DESTROY)
		err = pthread_mutex_destroy(mutex);
	else if (op == MUTEX_LOCK)
		err = pthread_mutex_lock(mutex);
	else if (op == MUTEX_UNLOCK)
		err = pthread_mutex_unlock(mutex);
	if (err)
		perr(name, errno);
	return (err);
}

void	destroy_mutexes(t_input *input, t_philo *philos, int end)
{
	int	i;

	mutex_op(&input->global_state, MUTEX_DESTROY, DESTROY);
	i = 0;
	while (i < end)
	{
		mutex_op(input->forks + i, MUTEX_DESTROY, DESTROY);
		mutex_op(&philos[i].state, MUTEX_DESTROY, DESTROY);
		i++;
	}
}
