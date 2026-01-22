/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:28:11 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/22 22:25:17 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sim_eat(t_philo *philo);
static void	sim_sleep(t_philo *philo);
static void	sim_think(t_philo *philo);
static void	update_meal_state(t_philo *philo);

void	run_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_sleep(5 * 1e3);
	if (philo->id % 2 && philo->id == philo->input->philos)
		precise_sleep((philo->input->time_to_eat + 10) * 1e3);
	while (!sim_done(philo->input) && (philo->input->times_must_eat < 0
			|| read_int(&philo->state,
				&philo->meals_eaten) < philo->input->times_must_eat))
	{
		sim_eat(philo);
		if (sim_done(philo->input))
			break ;
		sim_sleep(philo);
		if (sim_done(philo->input))
			break ;
		sim_think(philo);
	}
}

// make meals eaten not read by monitor?

static void	sim_eat(t_philo *philo)
{
	if (mutex_op(philo->first_fork, MUTEX_LOCK, LOCK))
		return ;
	sim_print(philo, TAKE_FORK, NULL, false);
	if (mutex_op(philo->second_fork, MUTEX_LOCK, LOCK))
	{
		mutex_op(philo->first_fork, MUTEX_UNLOCK, UNLOCK);
		return ;
	}
	update_meal_state(philo);
	sim_print(philo, TAKE_FORK, EAT, false);
	precise_sleep(philo->input->time_to_eat * 1e3);
	mutex_op(philo->first_fork, MUTEX_UNLOCK, UNLOCK);
	mutex_op(philo->second_fork, MUTEX_UNLOCK, UNLOCK);
}

static void	sim_sleep(t_philo *philo)
{
	sim_print(philo, SLEEP, NULL, false);
	precise_sleep(philo->input->time_to_sleep * 1e3);
}

static void	sim_think(t_philo *philo)
{
	t_input		*input;
	long long	t_think;

	sim_print(philo, THINK, NULL, false);
	input = philo->input;
	if (input->philos % 2 == 0)
		return ;
	t_think = (input->time_to_eat * 2) - input->time_to_sleep;
	if (t_think > 0)
		precise_sleep(t_think * 1e3 * 0.35);
}

static void	update_meal_state(t_philo *philo)
{
	if (mutex_op(&philo->state, MUTEX_LOCK, LOCK))
		return ;
	philo->last_meal_time = get_time(false);
	philo->meals_eaten++;
	if (mutex_op(&philo->state, MUTEX_UNLOCK, UNLOCK))
		return ;
}
