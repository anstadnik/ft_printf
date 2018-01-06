/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:03:44 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/06 11:03:40 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Makes the string and prints it to the standart output
*/

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	va_list	arg_beg;
	char	*ret;
	int		rez;

	if (!format)
		return (0);//change to null
	va_start(arg, format);
	va_copy(arg_beg, arg);
	ret = NULL;
	rez = printf_make_str(&ret, format, arg, arg_beg);
	if (~rez)
		write(1, ret, (size_t)rez);
	free(ret);
	va_end(arg);
	va_end(arg_beg);
	return (rez);
}

/*
** Makes the string and prints it to the given fd
*/

/*
int	ft_dprintf(int fd, const char *format, ...)
{
	return (0);
}
*/

/*
** Makes the string, allocates enough memory to the given pointer to the char,
** and puts the output string there
*/

/*
int	ft_asprintf(char **ret, const char *format, ...)
{
	return (0);
}
*/
