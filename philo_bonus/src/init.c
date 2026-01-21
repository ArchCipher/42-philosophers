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

/*
sem_t * sem_open(const char *name, int oflag, ...);

int sem_close(sem_t *sem);
The system resources associated with the named semaphore referenced by sem are
deallocated and the descriptor is invalidated.

int
     sem_unlink(const char *name);
The named semaphore named name is removed.
If the semaphore is in use by other processes, then name is immediately
disassociated with the semaphore, but the semaphore itself will not be removed
until all references to it have been closed.
Subsequent calls to sem_open() using name will refer to or create a new
semaphore named name.
*/

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

/*
Parent:
  sem_unlink(old)
  sem_open(new)
  fork N children
  wait for children
  sem_close

Children:
  inherit semaphore
  use it
  sem_close
  exit

Kernel:
  destroys semaphore automatically
*/