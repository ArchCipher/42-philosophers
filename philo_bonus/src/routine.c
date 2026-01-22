/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:28:11 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/22 22:21:03 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sim_eat(t_philo *philo);
static void	sim_sleep(t_philo *philo);
static void	sim_think(t_philo *philo);
static void	sim_print(t_philo *philo, const char *msg1, const char *msg2);

void	run_sim(t_philo *philo)
{
	while (1)
	{
		sim_eat(philo);
		if (philo->meals_eaten == philo->input->times_must_eat)
			return ;
		sim_sleep(philo);
		sim_think(philo);
	}
}

static void	sim_eat(t_philo *philo)
{
	if (sem_wait(philo->input->forks))
		error_exit_child(WAIT, errno);
	sim_print(philo, TAKE_FORK, NULL);
	if (sem_wait(philo->input->forks))
	{
		sem_post(philo->input->forks);
		error_exit_child(WAIT, errno);
	}
	philo->last_meal_time = get_time(false);
	philo->meals_eaten++;
	sim_print(philo, TAKE_FORK, EAT);
	if (philo->meals_eaten != philo->input->times_must_eat)
		precise_sleep(philo->input->time_to_eat * 1e3);
	if (sem_post(philo->input->forks))
		error_exit_child(POST, errno);
	if (sem_post(philo->input->forks))
		error_exit_child(POST, errno);
}

static void	sim_sleep(t_philo *philo)
{
	sim_print(philo, SLEEP, NULL);
	precise_sleep(philo->input->time_to_sleep * 1e3);
}

static void	sim_think(t_philo *philo)
{
	long long	t_think;

	sim_print(philo, THINK, NULL);
	if (philo->input->philos % 2 == 0)
		return ;
	t_think = (philo->input->time_to_eat * 2) - philo->input->time_to_sleep;
	if (t_think > 0)
		precise_sleep((t_think - 10) * 1e3);
}

/*
DESCRIPTION:
	Prints simulation status to stdout.
*/

void	sim_print(t_philo *philo, const char *msg1, const char *msg2)
{
	long long	now;
	long long	elapsed;

	if (sem_wait(philo->input->print))
		error_exit_child(WAIT, errno);
	now = get_time(false);
	elapsed = now - philo->input->sim_start;
	printf("%lld %d %s\n", elapsed, philo->id, msg1);
	if (msg2)
		printf("%lld %d %s\n", elapsed, philo->id, msg1);
	if (sem_post(philo->input->print))
		error_exit_child(POST, errno);
}
