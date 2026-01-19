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

static const char	*ft_strerror(int errnum);

void	perr(const char *function, int errnum)
{
	printf("%s: %s\n", function, ft_strerror(errnum));
}

static const char	*ft_strerror(int errnum)
{
	if (errnum == EPERM)
		return (E_PERM);
	if (errnum == ESRCH)
		return (E_SRCH);
	if (errnum == EDEADLK)
		return (E_DEADLK);
	if (errnum == ENOMEM)
		return (E_NOMEM);
	if (errnum == EFAULT)
		return (E_FAULT);
	if (errnum == EBUSY)
		return (E_BUSY);
	if (errnum == EINVAL)
		return (E_INVAL);
	if (errnum == EAGAIN)
		return (E_AGAIN);
	if (errnum == ENOTRECOVERABLE)
		return (E_NOTRECOVERABLE);
	if (errnum == EOWNERDEAD)
		return (E_OWNERDEAD);
	return ("Unknown error");
}
