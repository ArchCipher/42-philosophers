/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 20:02:45 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/18 20:59:09 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(int philo_nbr, int end, pthread_t *thread_ids);

/*
DESCRIPTION:
	Creates and manages threads for the simulation.
	Returns 1 on error and prints error message.
*/

int	create_manage_threads(t_input *input, t_philo *philos)
{
	int	i;

	if (pthread_create(&input->thread_ids[input->philos], NULL, monitor_sim,
			philos))
		return (perr(CREATE, errno), 1);
	i = 0;
	while (i < input->philos)
	{
		if (input->philos % 2 && i == input->philos - 1)
			precise_sleep(input->time_to_eat + 1);
		if (pthread_create(&input->thread_ids[i], NULL, run_sim, philos + i))
		{
			stop_simulation(input);
			join_threads(i, input->philos, input->thread_ids);
			return (perr(CREATE, errno), 1);
		}
		i++;
	}
	usleep (10 * 1000);
	join_threads(input->philos, input->philos, input->thread_ids);
	return (0);
}

/*
DESCRIPTION:
	Joins threads for the simulation.
	Returns 1 on error and prints error message.
*/
static void	join_threads(int philo_nbr, int end, pthread_t *thread_ids)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (pthread_join(thread_ids[i++], NULL))
			perr(JOIN, errno);
	}
	if (pthread_join(thread_ids[philo_nbr], NULL))
		perr(JOIN, errno);
}
