/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:44:12 by kmurugan          #+#    #+#             */
/*   Updated: 2026/01/18 19:44:14 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char *ft_strerror(int errnum)
{
	if (errnum == EPERM)// 1
		return (E_PERM);
	if (errnum == EAGAIN)//11
		return (E_AGAIN);
	if (errnum == EINVAL)// 22
		return (E_INVAL);
	if (errnum == EDEADLK)// 35
		return (E_DEADLK);
	if (errnum == ESRCH)// 3
		return (E_SRCH);
	if (errnum == EFAULT)// 14
		return (E_FAULT);
	if (errnum == ENOTRECOVERABLE)// 131
		return (E_NOTRECOVERABLE);
	if (errnum == EOWNERDEAD)// 130
		return (E_OWNERDEAD);
	if (errnum == EBUSY)
		return (E_BUSY);
	return ("Unknown error");
}
/*
create
join
mutex_destroy
gettimeofday

mutex unlock/lock
*/