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

void	error_exit_child(const char *name, int errnum)
{
	perr(name, errnum);
	exit(1);
}

void	perr(const char *name, int errnum)
{
	printf("%s: %s\n", name, ft_strerror(errnum));
}

static const char	*ft_strerror(int errnum)
{
	static const t_err	errs[] = {{ENOENT, "No such file or directory"},
	{EINTR, "Interrupted function call"},
	{EDEADLK, "Resource deadlock avoided"}, {ENOMEM, "Out of memory"},
	{EACCES, "Permission denied"}, {EEXIST, "File exists"},
	{EINVAL, "Invalid argument"}, {ENFILE, "Too many open files in system"},
	{EMFILE, "Too many open files"}, {ENOSPC, "Device out of space"},
	{ERANGE, "Numerical result out of range"},
	{EAGAIN, "Resource temporarily unavailable"},
	{ENAMETOOLONG, "File name too long"}};
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
