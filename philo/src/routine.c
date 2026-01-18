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

void	update_meal_state(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->state))
		return ;
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	if (pthread_mutex_unlock(&philo->state))
		return ;
}

int	sim_eat(t_philo *philo)
{
	int	ret;

	if (pthread_mutex_lock(philo->left_fork))
		return (1);
	sim_print(philo, TAKE_FORK);
	if (pthread_mutex_lock(philo->right_fork))
		return (pthread_mutex_unlock(philo->left_fork), 1);
	sim_print(philo, TAKE_FORK);
	sim_print(philo, EAT);
	update_meal_state(philo);
	usleep(philo->input->time_to_eat * 1000);
	ret = 0;
	if (pthread_mutex_unlock(philo->left_fork))
		ret = 1;
	if (pthread_mutex_unlock(philo->right_fork))
		ret = 1;
	return (ret);
}

int	sim_sleep(t_philo *philo)
{
	sim_print(philo, SLEEP);
	usleep(philo->input->time_to_sleep * 1000);
	return (0);
}

int	sim_think(t_philo *philo)
{
	sim_print(philo, THINK);
	usleep(1 * 1000);
	return (0);
}

void	*run_sim(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->input->philos == 1)
	{
		if (pthread_mutex_lock(philo->left_fork))
			return (NULL);
		sim_print(philo, TAKE_FORK);
		usleep(philo->input->time_to_die * 1000);
		pthread_mutex_unlock(philo->right_fork);
		return (NULL);
	}
	while (!should_stop_sim(philo->input))
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
