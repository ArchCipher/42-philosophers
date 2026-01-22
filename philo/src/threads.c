/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 20:02:45 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/22 22:25:24 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_thread(t_input *input, t_philo *philos, int i);
static void	join_threads(int end, pthread_t *thread_ids);
static void	init_last_meal_time(t_input *input, t_philo *philos);

/*
DESCRIPTION:
	Creates and manages threads for the simulation.
	Returns 1 on error and prints error message.
*/

int	create_manage_threads(t_input *input, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < input->philos)
	{
		if (create_thread(input, philos, i))
			return (1);
		i++;
	}
	init_last_meal_time(input, philos);
	input->threads_ready = 1;
	if (pthread_create(&input->thread_ids[input->philos], NULL, monitor_sim,
			philos))
		return (perr(CREATE, errno), 1);
	precise_sleep(2 * 1e3);
	join_threads(input->philos, input->thread_ids);
	if (pthread_join(input->thread_ids[input->philos], NULL))
		perr(JOIN, errno);
	return (0);
}

static int	create_thread(t_input *input, t_philo *philos, int i)
{
	if (pthread_create(&input->thread_ids[i], NULL, run_sim, philos + i) == 0)
		return (0);
	stop_sim(input);
	perr(CREATE, errno);
	join_threads(i, input->thread_ids);
	return (1);
}

static void	init_last_meal_time(t_input *input, t_philo *philos)
{
	int	i;

	input->sim_start = get_time(false);
	i = 0;
	while (i < input->philos)
	{
		philos[i].last_meal_time = input->sim_start;
		i++;
	}
}

/*
DESCRIPTION:
	Joins threads for the simulation.
	Returns 1 on error and prints error message.
*/
static void	join_threads(int end, pthread_t *thread_ids)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (pthread_join(thread_ids[i], NULL))
			perr(JOIN, errno);
		i++;
	}
}

void	*run_sim(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->input->threads_ready)
	{
		if (read_int(&philo->input->global_state,
				&philo->input->sim_done))
			return (NULL);
		precise_sleep(1e3);
	}
	if (philo->input->philos == 1)
	{
		sim_print(philo, TAKE_FORK, NULL, false);
		while (!sim_done(philo->input))
			precise_sleep(1e3);
		return (NULL);
	}
	run_routine(philo);
	return (NULL);
}
