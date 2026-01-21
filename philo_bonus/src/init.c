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

static int open_sem(const char *name, sem_t **sem, int n);

// on linux implemented under /dev/shm/sem.forks

int init_sem(t_input *input)
{
    sem_unlink("/forks");
    sem_unlink("/print");
    if (open_sem("/forks", &input->forks, input->philos))
        return (1);
    if (open_sem("/print", &input->print, 1))
        return (sem_close(input->forks), 1);
    return (0);
}

static int open_sem(const char *name, sem_t **sem, int n)
{
    *sem = sem_open(name, O_CREAT, 0666, n);
    if (*sem == SEM_FAILED)
        return (perr(OPEN, errno), 1);
    return (0);
}
