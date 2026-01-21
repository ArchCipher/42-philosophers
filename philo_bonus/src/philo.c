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

void	exec_child(t_philo *philo)
{
	if (pthread_create(&philo->thread_id, NULL, monitor_sim, philo))
	{
		perr(CREATE, errno);
		exit(-1);
	}
	run_sim(philo);
	if (pthread_join(philo->thread_id, NULL))
		perr(JOIN, errno);
	sem_close(philo->input->forks);
	sem_close(philo->input->print);
	exit (0);
}

int	fork_processes(t_input *input)
{
	t_philo	philo;
	int		i;

	i = 0;
	while (i < input->philos)
	{
		input->pids[i] = fork();
		if (input->pids[i] == -1)
			return (perr("fork", errno), 1);
		if (input->pids[i] == 0)
		{
			philo.id = (i + 1) % input->philos;
			philo.meals_eaten = 0;
			philo.sim_done = 0;
			input->sim_start = get_time(false);
			philo.last_meal_time = input->sim_start;
			philo.input = input;
			exec_child(&philo);
		}
	}
	return (0);
}

// pid_t waitpid(pid_t pid, int *stat_loc, int options);
int	wait_processes(t_input *input)
{
	pid_t	child;
	int		status;
	int		i;

	child = waitpid(-1, &status, 0);
	i = 0;
	while(i < input->philos)
	{
		if (child != input->pids[i])
			kill(input->pids[i]);
		i++;
	}
	while(waitpid(-1, NULL, 0) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (SIG_EXIT_BASE + WTERMSIG(status));
	return (1);
}


int	main(int ac, char **av)
{
	t_input	*input;
	int		ret;

	if (ac != 5 && ac != 6)
		return (printf("USAGE: ./%s %s %s\n", PROG, E_ARGS1, E_ARGS2));
	if (parse_input(av, input))
		return (1);
	if (av[5] && input->times_must_eat)
		return (0);
	if (init_sem(input))
		return (1);
	input->pids = malloc(sizeof(pid_t) * input->philos);
	ret = 1;
	if (input->pids)
	{
		fork_processes(input);
		ret = wait_processes(input);
		free(input->pids);
	}
	sem_close(input->forks);
	sem_close(input->print);
	return (ret);
}
