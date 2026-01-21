/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:28:11 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/18 20:51:31 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_sim(t_philo *philo);
static void	sim_eat(t_philo *philo);
static void	sim_sleep(t_philo *philo);
// static void	sim_think(t_philo *philo);
static void	sim_print(t_philo *philo, const char *msg);

void	exec_child(t_input *input, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.meals_eaten = 0;
	philo.last_meal_time = input->sim_start;
	philo.input = input;
	if (pthread_create(&philo.thread_id, NULL, monitor_sim, &philo))
		error_exit_child(CREATE, errno);
	pthread_detach(philo.thread_id);
	run_sim(&philo);
	exit (0);
}

void	run_sim(t_philo *philo)
{
	while (1)
	{
		sim_eat(philo);
		if (philo->meals_eaten == philo->input->times_must_eat)
			return ;
		sim_sleep(philo);
		sim_print(philo, THINK);
	}
}

static void	sim_eat(t_philo *philo)
{
	if (sem_wait(philo->input->forks))
		error_exit_child(WAIT, errno);
	sim_print(philo, TAKE_FORK);
	if (sem_wait(philo->input->forks))
	{
		sem_post(philo->input->forks);
		error_exit_child(WAIT, errno);
	}
	sim_print(philo, TAKE_FORK);
	philo->last_meal_time = get_time(false);
	philo->meals_eaten++;
	sim_print(philo, EAT);
	if (philo->meals_eaten != philo->input->times_must_eat)
		precise_sleep(philo->input->time_to_eat * 1e3);
	if (sem_post(philo->input->forks))
		error_exit_child(POST, errno);
	if (sem_post(philo->input->forks))
		error_exit_child(POST, errno);
}

static void	sim_sleep(t_philo *philo)
{
	sim_print(philo, SLEEP);
	precise_sleep(philo->input->time_to_sleep * 1e3);
}

// static void	sim_think(t_philo *philo)
// {
// 	sim_print(philo, THINK);
// }

/*
DESCRIPTION:
	Prints simulation status to stdout.
*/

void	sim_print(t_philo *philo, const char *msg)
{
	long long	now;
	long long	elapsed;

	if (sem_wait(philo->input->print))
		error_exit_child(WAIT, errno);
	now = get_time(false);
	elapsed = now - philo->input->sim_start;
	printf("%lld %d %s\n", elapsed, philo->id, msg);
	if (sem_post(philo->input->print))
		error_exit_child(POST, errno);
}
