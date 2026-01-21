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

void	perr(const char *name, int errnum)
{
	printf("%s: %s\n", name, ft_strerror(errnum));
}

static const char	*ft_strerror(int errnum)
{
	static const t_err	errs[] = {{EPERM, "Operation not permitted"},
	{ESRCH, "No such process"}, {EDEADLK, "Resource deadlock avoided"},
	{ENOMEM, "Out of memory"}, {EFAULT, "Bad address"},
	{EBUSY, "Device or resource busy"}, {EINVAL, "Invalid argument"},
	{ERANGE, "Numerical result out of range"},
	{EAGAIN, "Resource temporarily unavailable"},
	{ENOTRECOVERABLE, "State not recoverable"}, {EOWNERDEAD, "Owner died"}};
	unsigned long		i;

	i = 0;
	while (i < (sizeof(errs) / sizeof(errs[0])))
	{
		if (errs[i].code == errnum)
			return (errs[i].msg);
		i++;
	}
	return ("Unknown error");
}

