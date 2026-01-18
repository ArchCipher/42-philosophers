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

	i = 0;
	while (i < philos->input->philos)
	{
		if (read_data(&philos[i].state,
				&philos[i].meals_eaten) < philos->input->times_must_eat)
			return (0);
		i++;
	}
	return (1);
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
		if (sim_done(philos))
			return (stop_simulation(philos), NULL);
		i = 0;
		while (i < philos->input->philos)
		{
			if (get_time() - read_data(&philos[i].state,
					&philos[i].last_meal_time) >= philos->input->time_to_die)
			{
				sim_print(philos + i, DEATH);
				stop_simulation(philos);
				return (NULL);
			}
			i++;
		}
		usleep(philos->input->time_to_die * 1000);
	}
	return (NULL);
}
