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

/*
DESCRIPTION:
	Gets the current time in milliseconds.
	Returns -1 on error and prints error message.
*/

long long	get_time(bool usec)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
		return (perr("gettimeofday", errno), -1);
	if (usec)
		return ((tp.tv_sec * 1e6) + tp.tv_usec);
	return ((tp.tv_sec * 1e3) + (tp.tv_usec / 1e3));
}

/*
DESCRIPTION:
	Prints simulation status to stdout.
*/

void	sim_print(t_philo *philo, const char *action, bool is_death)
{
	long long	now;

	now = get_time(false);
	if (now < 0)
		return ;
	if (mutex_op(&philo->input->global_state, MUTEX_LOCK, LOCK))
		return ;
	if (!philo->input->sim_done || is_death)
		printf("%lld %d %s\n", now - philo->input->sim_start, philo->id,
			action);
	if (mutex_op(&philo->input->global_state, MUTEX_UNLOCK, UNLOCK))
		return ;
}

/*
DESCRIPTION:
	Reads an int value from a mutex.
	Returns -1 on error.
*/

int	read_int(pthread_mutex_t *mutex, int *data)
{
	int	ret;

	if (mutex_op(mutex, MUTEX_LOCK, LOCK))
		return (-1);
	ret = *data;
	if (mutex_op(mutex, MUTEX_UNLOCK, UNLOCK))
		return (-1);
	return (ret);
}

int	sim_done(t_input *input)
{
	return (read_int(&input->global_state, &input->sim_done));
}

void	precise_sleep(long long usec)
{
	long long	start;
	long long	rem;

	start = get_time(true);
	if (start < 0)
		return ;
	while (get_time(true) - start < usec)
	{
		// if (should_stop_sim(input))
		// 	break ;
		rem = usec - (get_time(true) - start);
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time(true) - start < usec)
				;
		}
	}
}
