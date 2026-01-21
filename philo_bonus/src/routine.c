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

void	run_sim(t_philo *philo)
{
	int	must_eat;

	must_eat = philo->input->times_must_eat;
	while (!philo->sim_done)
	{
		sim_eat(philo);
		if (philo->sim_done)
			break ;
		sim_sleep(philo);
		if (philo->sim_done)
			break ;
		sim_think(philo);
	}
}

// make meals eaten not read by monitor?

static void	sim_eat(t_philo *philo)
{
	if (sem_wait(philo->input->forks))
		return ;
	sim_print(philo, TAKE_FORK);
	if (sem_wait(philo->input->forks))
	{
		sem_post(philo->input->forks);
		return ;
	}
	sim_print(philo, TAKE_FORK);
	philo->last_meal_time = get_time(false);
	philo->meals_eaten++;
	sim_print(philo, EAT);
	if (philo->meals_eaten == philo->input->times_must_eat)
	{
		philo->sim_done = 1;
		return ;
	}
	precise_sleep(philo->input->time_to_eat * 1e3);
	sem_post(philo->input->forks);
	sem_post(philo->input->forks);
}

static void	sim_sleep(t_philo *philo)
{
	sim_print(philo, SLEEP);
	precise_sleep(philo->input->time_to_sleep * 1e3);
}

static void	sim_think(t_philo *philo)
{
	// t_input		*input;
	// long long	t_think;

	sim_print(philo, THINK);
	// input = philo->input;
	// if (input->philos % 2 == 0)
	// 	return ;
	// t_think = (input->time_to_eat * 2) - input->time_to_sleep;
	// if (t_think > 0)
	// 	precise_sleep((t_think - 2) * 1e3);
}
