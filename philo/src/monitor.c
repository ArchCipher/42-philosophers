/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:35:10 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/18 20:18:07 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			sim_done(t_philo *philos);
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
	while (!should_stop_sim(philos->input))
	{
		if (philos->input->times_must_eat > 0 && sim_done(philos))
			return (stop_simulation(philos->input), NULL);
		i = 0;
		while (i < philos->input->philos)
		{
			if (philos->input->times_must_eat > 0 && philo_dead(philos + i))
			{
				stop_simulation(philos->input);
				sim_print(philos + i, DEATH, true);
				return (NULL);
			}
			i++;
		}
		precise_sleep(5);
	}
	return (NULL);
}

/*
DESCRIPTION:
	Checks if all philosophers have eaten enough.
*/

static int	sim_done(t_philo *philos)
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
	long long	now;
	long long	last_meal;

	meals_eaten = read_int(&philo->state, &philo->meals_eaten);
	if (meals_eaten < 0 || meals_eaten >= philo->input->times_must_eat)
		return (0);
	now = get_time();
	last_meal = read_long_long(&philo->state, &philo->last_meal_time);
	if (now < 0 || last_meal < 0)
		return (0);
	if (now - last_meal <= philo->input->time_to_die)
		return (0);
	return (1);
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

void	stop_simulation(t_input *input)
{
	if (pthread_mutex_lock(&input->global_state))
		return ;
	input->sim_stop = 1;
	pthread_mutex_unlock(&input->global_state);
}
