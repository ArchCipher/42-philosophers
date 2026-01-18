/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:44:25 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/18 20:59:09 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

/*
	NAME
		philo
	USAGE
		./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
		[number_of_times_each_philosopher_must_eat]
	DESCRIPTION:
		Philosophers with threads and mutexes
	EXTERNAL FUNC(S)
		memset, printf, malloc, free, write,
		usleep, gettimeofday, pthread_create,
		pthread_detach, pthread_join, pthread_mutex_init,
		pthread_mutex_destroy, pthread_mutex_lock,
		pthread_mutex_unlock
*/

/*
• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
*/

void	destroy_mutexes(t_input *input, t_philo *philos)
{
	int	i;

	if (pthread_mutex_destroy(&input->global_state))
		printf("pthread_mutex_destroy: %s\n", ft_strerror(errno));
	i = 0;
	while (i < input->philos)
	{
		if (pthread_mutex_destroy(input->forks + i))
			printf("pthread_mutex_destroy: %s\n", ft_strerror(errno));
		if (pthread_mutex_destroy(&philos[i].state))
			printf("pthread_mutex_destroy: %s\n", ft_strerror(errno));
		i++;
	}
}

int	main(int ac, char **av)
{
	t_input	input;
	t_philo *philos;

	if (ac != 5 && ac != 6)
		return (printf("USAGE: ./philo %s %s\n", E_ARGS1, E_ARGS2));
	if (parse_input(av, &input))
		return (1);
	if (av[5] && !input.times_must_eat)
		return (0);
	philos = malloc(sizeof(t_philo) * input.philos);
	if (!philos)
		return (printf("malloc: %s\n", E_NOMEM), 1);
	if (init_philo(&input, philos))
		return (free(philos), 1);
	create_manage_threads(&input, philos);
	destroy_mutexes(&input, philos);
	free(philos);
	free(input.thread_ids);
	free(input.forks);
	return (0);
}
