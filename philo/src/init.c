/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:47:42 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/18 20:57:30 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_input *input, t_philo *philos)
{
	int	i;

	input->forks = malloc(sizeof(pthread_mutex_t) * input->philos);
	if (!input->forks)
		return (printf("malloc: %s\n", E_NOMEM), 1);
	if (pthread_mutex_init(&input->global_state, NULL))
		return (printf("pthread_mutex_init: %s\n", ft_strerror(errno)), 1);
	i = 0;
	while (i < input->philos)
	{
		if (pthread_mutex_init(input->forks + i, NULL))
			return (printf("pthread_mutex_init: %s\n", ft_strerror(errno)), 1);
		if (pthread_mutex_init(&philos[i].state, NULL))
			return (printf("pthread_mutex_init: %s\n", ft_strerror(errno)), 1);
		i++;
	}
	return (0);
}

int	init_threads(t_input *input, t_philo *philos)
{
	int	i;

	input->thread_ids = malloc(sizeof(pthread_t) * (input->philos + 1));
	if (!input->thread_ids)
		return (printf("malloc: %s\n", E_NOMEM), 1);
	i = 0;
	while (i < input->philos)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = input->forks + i;
		philos[i].right_fork = input->forks + ((i + 1) % input->philos);
		philos[i].last_meal_time = get_time();
		philos[i].meals_eaten = 0;
		philos[i].input = input;
		i++;
	}
	return (0);
}

int init_philo(t_input *input, t_philo *philos)
{
	if (init_mutexes(input, philos))
		return (1);
	if (init_threads(input, philos))
		return (free(input->forks), 1);
	return (0);
}
