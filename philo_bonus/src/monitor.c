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


static int			philo_dead(t_philo *philo);

/*
DESCRIPTION:
	Monitors the simulation and stops it if the philosophers have eaten enough
	or if a philosopher has died.
*/

void	*monitor_sim(void *arg)
{
	t_philo		*philo;
	long long	start;

	philo = (t_philo *)arg;
	start = philo->input->sim_start;
	while (!philo_dead(philo))
		precise_sleep(2 * 1e3);
	if (sem_wait(philo->input->print))
		error_exit_child(WAIT, errno);
	printf("%lld %d %s\n", get_time(false) - start, philo->id, DEATH);
	exit (1);
	return (NULL);
}

/*
DESCRIPTION:
	Checks if a philosopher has died.
*/

static int	philo_dead(t_philo *philo)
{
	int	must_eat;
	int	t_to_die;

	must_eat = philo->input->times_must_eat;
	t_to_die = philo->input->time_to_die;
	if (must_eat > 0 && philo->meals_eaten >= must_eat)
		return (0);
	return (get_time(false) - philo->last_meal_time >= t_to_die);
}
