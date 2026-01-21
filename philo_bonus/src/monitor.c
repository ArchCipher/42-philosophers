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
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (!philo->sim_done)
	{
		if (philo_dead(philo))
		{
			philo->sim_done = 1;
			sim_print(philo, DEATH);
			return (NULL);
		}
		precise_sleep(2 * 1e3);
	}
	return (NULL);
}

/*
DESCRIPTION:
	Checks if all philosophers have eaten enough.
*/

static int	philo_full(t_philo *philo)
{
	int	meals_eaten;

	if (philo->meals_eaten < philo->input->times_must_eat)
		return (0);
	return (1);
}

/*
DESCRIPTION:
	Checks if a philosopher has died.
*/

static int	philo_dead(t_philo *philo)
{
	int			must_eat;
	long long	now;

	must_eat = philo->input->times_must_eat;
	if (philo->input->philos > 1 && must_eat < 0)
		return (0);
	if (philo->meals_eaten >= must_eat)
		return (0);
	now = get_time(false);
	if (now < 0)
		return (0);
	if (now - philo->last_meal_time < philo->input->time_to_die)
		return (0);
	return (1);
}
