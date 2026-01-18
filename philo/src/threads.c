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

// in case of failure should pass i and philo_nbr
void	join_threads(int philo_nbr, int end, pthread_t *thread_ids)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (pthread_join(thread_ids[i++], NULL))
			printf("pthread_join: %s\n", ft_strerror(errno));
	}
	if (pthread_join(thread_ids[philo_nbr], NULL))
		printf("pthread_join: %s\n", ft_strerror(errno));
}


/*
ERRORS
		The pthread_mutex_destroy() function will fail if:

		[EINVAL]           The value specified by mutex is invalid.

		[EBUSY]            Mutex is locked.
*/

void	stop_simulation(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->input->global_state))
		return ;
	philo->input->sim_stop = 1;
	pthread_mutex_unlock(&philo->input->global_state);
}

// start routine - eat? or think or sleep?
// when create_fails set sim_stop, join any created threads
int	create_manage_threads(t_input *input, t_philo *philos)
{
	int	i;

	input->sim_start = get_time();
	if (pthread_create(&input->thread_ids[input->philos], NULL, monitor_sim,
			philos))
		return (printf("pthread_create: %s\n", ft_strerror(errno)), 1);
	i = 1;
	while (i < input->philos)
	{
		if (pthread_create(&input->thread_ids[i], NULL, run_sim, philos + i))
		{
			stop_simulation(philos + i);
			join_threads(i, input->philos, input->thread_ids);
			return (printf("pthread_create: %s\n", ft_strerror(errno)), 1);
		}
		i+=2;
	}
	i = 0;
	usleep (10 * 1000);
	while (i < input->philos)
	{
		if (pthread_create(&input->thread_ids[i], NULL, run_sim, philos + i))
		{
			stop_simulation(philos + i);
			join_threads(i, input->philos, input->thread_ids);
			return (printf("pthread_create: %s\n", ft_strerror(errno)), 1);
		}
		i+=2;
	}
	join_threads(input->philos, input->philos, input->thread_ids);
	return (0);
}
