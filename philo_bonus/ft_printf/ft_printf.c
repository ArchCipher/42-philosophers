/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:27:53 by kmurugan          #+#    #+#             */
/*   Updated: 2025/11/19 17:50:15 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	NAME
		ft_printf
	SYNOPSIS
		#include "ft_printf.h"
	PROTOTYPE
		int ft_printf(const char *, ...);
	DESCRIPTION:
		Prints a formatted string to the standard output.
		Conversions are: cspdiuxX%
	RETURN VALUE
		Returns the number of characters printed.
		The printf utility exits 0 on success, and >0 if an error occurs.
	EXTERNAL FUNC(S)
		write, va_start, va_arg, va_end
		ft_vdprintf
*/

/*
	STDARG (3) / va_arg
	stdarg  variable argument lists
	va_list	<variable_name>
			structure used by the following functions / macros

	VARIADIC FUNCTIONS / MACROS
	void	va_start(va_list ap, last);			// initializes ap
	type	va_arg(va_list ap, type);	// returns n bytes after 1st param
	void	va_copy(va_list dest, va_list src)	//
	void	va_end(va_list ap);					// frees the ap
*/

int	ft_printf(const char *fmt, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, fmt);
	ret = ft_vdprintf(STDOUT_FILENO, fmt, ap);
	va_end(ap);
	return (ret);
}
