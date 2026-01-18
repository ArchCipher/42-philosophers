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

int	sim_done(t_philo *philos)
{
	int	i;
	int	meals_eaten;

	i = 0;
	while (i < philos->input->philos)
	{
		meals_eaten = read_data(&philos[i].state, &philos[i].meals_eaten);
		if (meals_eaten < philos->input->times_must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	sim_print_death(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->input->global_state))
		return ;
	printf("%lld %d %s\n", get_time() - philo->input->sim_start, philo->id, DEATH);
	if (pthread_mutex_unlock(&philo->input->global_state))
		return ;
}

// if all philos have eaten 3 meals
// if last_meal_time > time_to_die
// then update sim_stop and print death message
// should_stop_sim will return 1 if lock or unlock fails- which would stop simulation
void	*monitor_sim(void *arg)
{
	t_philo *philos;
	int i;

	philos = (t_philo *)arg;
	while (!should_stop_sim(philos->input))
	{
		if (philos->input->times_must_eat != -1 && sim_done(philos))
			return (stop_simulation(philos), NULL);
		i = 0;
		while (i < philos->input->philos)
		{
			if (get_time() - read_data(&philos[i].state,
					&philos[i].last_meal_time) >= philos->input->time_to_die)
			{
				stop_simulation(philos);
				sim_print_death(philos + i);
				return (NULL);
			}
			i++;
		}
		usleep(philos->input->time_to_die * 1000);
	}
	return (NULL);
}
