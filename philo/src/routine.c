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

static void	sim_eat(t_philo *philo);
static void	sim_sleep(t_philo *philo);
static void	sim_think(t_philo *philo);
static void	update_meal_state(t_philo *philo);

void	*run_sim(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->input->philos == 1)
	{
		sim_print(philo, TAKE_FORK, false);
		while (!should_stop_sim(philo->input))
			usleep(1000);
		return (NULL);
	}
	if (philo->id % 2)
		usleep(1000);
	while (!should_stop_sim(philo->input) && (philo->input->times_must_eat <= 0
			|| read_int(&philo->state,
				&philo->meals_eaten) < philo->input->times_must_eat))
	{
		sim_eat(philo);
		if (should_stop_sim(philo->input))
			break ;
		sim_sleep(philo);
		if (should_stop_sim(philo->input))
			break ;
		sim_think(philo);
	}
	return (NULL);
}

// make meals eaten not read by monitor?

static void	sim_eat(t_philo *philo)
{
	if (mutex_op(philo->first_fork, MUTEX_LOCK, LOCK))
		return ;
	sim_print(philo, TAKE_FORK, false);
	if (mutex_op(philo->second_fork, MUTEX_LOCK, LOCK))
	{
		mutex_op(philo->first_fork, MUTEX_UNLOCK, UNLOCK);
		return ;
	}
	sim_print(philo, TAKE_FORK, false);
	update_meal_state(philo);
	sim_print(philo, EAT, false);
	precise_sleep(philo->input->time_to_eat);
	mutex_op(philo->first_fork, MUTEX_UNLOCK, UNLOCK);
	mutex_op(philo->second_fork, MUTEX_UNLOCK, UNLOCK);
}

static void	sim_sleep(t_philo *philo)
{
	sim_print(philo, SLEEP, false);
	precise_sleep(philo->input->time_to_sleep);
}

static void	sim_think(t_philo *philo)
{
	t_input		*input;
	long long	t_think;

	sim_print(philo, THINK, false);
	input = philo->input;
	if (input->philos % 2 == 0)
		return ;
	t_think = (input->time_to_eat * 2) - input->time_to_sleep;
	if (t_think > 0)
		precise_sleep(t_think - 10);
}

static void	update_meal_state(t_philo *philo)
{
	if (mutex_op(&philo->state, MUTEX_LOCK, LOCK))
		return ;
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	if (mutex_op(&philo->state, MUTEX_UNLOCK, UNLOCK))
		return ;
}
