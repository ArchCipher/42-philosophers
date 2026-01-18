/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:44:20 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/18 19:44:21 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// maybe wrappers should free memory and exit?

long long get_time(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
		return (printf("gettimeofday: %s\n", ft_strerror(errno)), 0);
	return ((tp.tv_sec * 1000) + (tp.tv_usec * 0.001));
}

void	sim_print(t_philo *philo, const char *action)
{
	if (pthread_mutex_lock(&philo->input->global_state))
		return ;
	if (!philo->input->sim_stop)
		printf("%lld %d %s\n", get_time() - philo->input->sim_start, philo->id, action);
	if (pthread_mutex_unlock(&philo->input->global_state))
		return ;
}

// exit and not return as return 1 is wrong
// but needs to cleanup if exits
// or return -1
long long	read_data(pthread_mutex_t *state, void *data)
{
	long long	ret;

	if (pthread_mutex_lock(state))
		return (1);
	ret = *((long long *)data);
	if (pthread_mutex_unlock(state))
		return (1);
	return (ret);
}

// must read and write while locked state

int	should_stop_sim(t_input *input)
{
	return (read_data(&input->global_state, &input->sim_stop));
}
