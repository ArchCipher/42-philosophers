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
long long	get_time_safe(bool usec)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
	{
		perr("gettimeofday", errno);
		return (-1);
	}
	if (usec)
		return ((tp.tv_sec * 1e6) + tp.tv_usec);
	return ((tp.tv_sec * 1e3) + (tp.tv_usec / 1e3));
}

long long	get_time(bool usec)
{
	long long	ret;

	ret = get_time_safe(usec);
	if (ret < 0)
		exit(1);
	return (ret);
}

void	precise_sleep(long long usec)
{
	long long	start;
	long long	rem;

	start = get_time(true);
	while (get_time(true) - start < usec)
	{
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
