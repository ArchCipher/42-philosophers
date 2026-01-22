/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:35:10 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/22 22:24:22 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			philo_full(t_philo *philos);
static int			philo_dead(t_philo *philo);
static long long	read_long_long(pthread_mutex_t *mutex, long long *data);

/*
DESCRIPTION:
	Monitors the simulation and stops it if the philosophers have eaten enough
	or if a philosopher has died.
*/

void	*monitor_sim(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (!sim_done(philos->input))
	{
		if (philos->input->times_must_eat > 0 && philo_full(philos))
			return (stop_sim(philos->input), NULL);
		i = 0;
		while (i < philos->input->philos)
		{
			if (philo_dead(philos + i))
			{
				stop_sim(philos->input);
				sim_print(philos + i, DEATH, NULL, true);
				return (NULL);
			}
			i++;
		}
		precise_sleep(1 * 1e3);
	}
	return (NULL);
}

/*
DESCRIPTION:
	Checks if all philosophers have eaten enough.
*/

static int	philo_full(t_philo *philos)
{
	int	i;
	int	meals_eaten;

	i = 0;
	while (i < philos->input->philos)
	{
		meals_eaten = read_int(&philos[i].state, &philos[i].meals_eaten);
		if (meals_eaten < philos->input->times_must_eat)
			return (0);
		i++;
	}
	return (1);
}

/*
DESCRIPTION:
	Checks if a philosopher has died.
*/

static int	philo_dead(t_philo *philo)
{
	int			meals_eaten;
	int			must_eat;
	long long	now;
	long long	last_meal;

	must_eat = philo->input->times_must_eat;
	meals_eaten = read_int(&philo->state, &philo->meals_eaten);
	if (meals_eaten < 0 || (must_eat > 0 && meals_eaten >= must_eat))
		return (0);
	now = get_time(false);
	last_meal = read_long_long(&philo->state, &philo->last_meal_time);
	if (now < 0 || last_meal < 0)
		return (0);
	if (now - last_meal < philo->input->time_to_die)
		return (0);
	return (1);
	// return (now - last_meal >= philo->input->time_to_die)
}

/*
DESCRIPTION:
	Reads a long long value from a mutex.
	Returns -1 on error.
*/

static long long	read_long_long(pthread_mutex_t *mutex, long long *data)
{
	long long	ret;

	if (mutex_op(mutex, MUTEX_LOCK, LOCK))
		return (-1);
	ret = *data;
	if (mutex_op(mutex, MUTEX_UNLOCK, UNLOCK))
		return (-1);
	return (ret);
}

void	stop_sim(t_input *input)
{
	if (pthread_mutex_lock(&input->global_state))
		return ;
	input->sim_done = 1;
	pthread_mutex_unlock(&input->global_state);
}
