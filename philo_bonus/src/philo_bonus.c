/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:44:25 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/22 22:20:58 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	fork_processes(t_input *input);
static void	exec_child(t_input *input, int id);
static int	wait_processes(t_input *input);
static void	cleanup(t_input *input);
/*
	NAME
		philo
	USAGE
		./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
		[number_of_times_each_philosopher_must_eat]
	DESCRIPTION:
		Philosophers with processes and semaphores
		Any change in simulation status is printed to stdout as follows:
			timestamp_in_ms X has taken a fork
			timestamp_in_ms X is eating
			timestamp_in_ms X is sleeping
			timestamp_in_ms X is thinking
			timestamp_in_ms X died
		where X is the philosopher number.
	EXTERNAL FUNC(S)
		memset, printf, malloc, free, write, fork, kill,
		exit, pthread_create, pthread_detach, pthread_join,
		usleep, gettimeofday, waitpid, sem_open, sem_close,
		sem_post, sem_wait, sem_unlink
*/

int	main(int ac, char **av)
{
	t_input	input;
	int		ret;

	if (ac != 5 && ac != 6)
		return (printf("USAGE: ./%s %s %s\n", PROG, E_ARGS1, E_ARGS2));
	if (parse_input(av, &input))
		return (1);
	if (av[5] && !input.times_must_eat)
		return (0);
	if (init_sem(&input))
		return (1);
	input.pids = malloc(sizeof(pid_t) * input.philos);
	ret = 1;
	if (input.pids && fork_processes(&input) >= 0)
		ret = wait_processes(&input);
	cleanup(&input);
	return (ret);
}

/*
DESCRIPTION:
	Fork processes and initialize the simulation.
*/

static int	fork_processes(t_input *input)
{
	int		i;

	memset(input->pids, -1, sizeof(pid_t) * input->philos);
	i = 0;
	while (i < input->philos)
	{
		input->pids[i] = fork();
		if (input->pids[i] == -1)
			return (perr("fork", errno), 1);
		if (input->pids[i] == 0)
			exec_child(input, i + 1);
		i++;
	}
	i = 0;
	while (i < input->philos)
	{
		if (sem_post(input->start))
		{
			perr("sem_post", errno);
			kill(input->pids[0], SIGTERM);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	exec_child(t_input *input, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.meals_eaten = 0;
	philo.input = input;
	if (sem_wait(input->start))
		error_exit_child(WAIT, errno);
	input->sim_start = get_time(false);
	philo.last_meal_time = input->sim_start;
	if (pthread_create(&philo.thread_id, NULL, monitor_sim, &philo))
		error_exit_child(CREATE, errno);
	pthread_detach(philo.thread_id);
	run_sim(&philo);
	exit (0);
}

/*
DESCRIPTION:
	Wait for processes to finish and clean up.
	In case of SIGINT(ctrl+c), it may leave orphaned processes and semaphores.
	The subject does not allow signal or sigaction, so there is no way to handle this
	without a signal handler.
*/

static int	wait_processes(t_input *input)
{
	pid_t	child;
	int		status;
	int		i;

	child = waitpid(-1, &status, 0);
	if (child == -1)
		return (perr("waitpid", errno), 1);
	i = 0;
	while (i < input->philos)
	{
		if (input->pids[i] != -1 && child != input->pids[i])
			kill(input->pids[i], SIGTERM);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (SIG_EXIT_BASE + WTERMSIG(status));
	return (1);
}

/*
DESCRIPTION:
	Cleans up the input and frees the memory.
*/

static void	cleanup(t_input *input)
{
	if (input->pids)
		free(input->pids);
	sem_close(input->forks);
	sem_close(input->print);
	sem_close(input->start);
}
