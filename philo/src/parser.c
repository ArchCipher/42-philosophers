/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:26:10 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/18 20:03:37 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str);
static int	ft_isspace(int c);
static int	ft_isdigit(int c);

// parser: positive number, no chars, max value
// timestamps > 60ms

int	parse_input(char **av, t_input *input)
{
	errno = 0;
	memset(input, 0, sizeof(t_input));
	input->philos = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	input->times_must_eat = -1;
	if (av[5])
		input->times_must_eat = ft_atoi(av[5]);
	if (errno || input->philos < 1)
		return (perr("philo", errno), 1);
	if (input->time_to_die < 60 || input->time_to_eat < 60
		|| input->time_to_sleep < 60)
		return (perr("philo", EINVAL), 1);
	if (!av[5])
		return (0);
	if (input->times_must_eat < 0)
		return (perr("philo", EINVAL), 1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	else if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		if (sign == 1 && (LONG_MAX - (num * 10)) < (*str - '0'))
			return (errno = ERANGE, (int)LONG_MAX);
		if (sign == -1 && (LONG_MAX - (num * 10)) < (*str - '0') - 1)
			return (errno = ERANGE, (int)LONG_MIN);
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (*str)
		errno = EINVAL;
	return ((int)(num * sign));
}

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
