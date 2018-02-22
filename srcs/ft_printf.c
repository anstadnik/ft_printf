/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:03:44 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/22 18:15:33 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Makes the string and prints it to the standart output
*/

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	char	*ret;
	ssize_t	rez;

	if (!format)
		return (-1);
	va_start(arg, format);
	ret = NULL;
	rez = printf_make_str(&ret, format, arg);
	if (rez > 0)
		write(1, ret, (size_t)rez);
	free(ret);
	va_end(arg);
	return ((int)rez);
}

/*
** Makes the string and prints it to the given fd
*/

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	arg;
	char	*ret;
	ssize_t	rez;

	if (!format || write(fd, NULL, 0) == -1)
		return (-1);
	va_start(arg, format);
	ret = NULL;
	rez = printf_make_str(&ret, format, arg);
	if (rez > 0)
		write(fd, ret, (size_t)rez);
	free(ret);
	va_end(arg);
	return ((int)rez);
}

/*
** Makes the string, allocates enough memory to the given pointer to the char,
** and puts the output string there
*/

int	ft_asprintf(char **ret, const char *format, ...)
{
	va_list	arg;
	ssize_t	rez;

	if (!format || !ret)
		return (-1);
	va_start(arg, format);
	*ret = NULL;
	rez = printf_make_str(ret, format, arg);
	va_end(arg);
	return ((int)rez);
}

/*
** Makes the string from given va_list and puts it to the given string
*/

int ft_vasprintf(char **ret, const char *format, va_list arg)
{
	ssize_t	rez;

	if (!format || !ret)
		return (-1);
	*ret = NULL;
	rez = printf_make_str(ret, format, arg);
	va_end(arg);
	return ((int)rez);
}


/*
** Makes the string from given va_list, and outputs it to the given fd
*/

int 		ft_vdprintf(int fd, const char *format, va_list arg)
{
	char	*ret;
	ssize_t	rez;

	if (!format || write(fd, NULL, 0) == -1)
		return (-1);
	ret = NULL;
	rez = printf_make_str(&ret, format, arg);
	if (rez > 0)
		write(fd, ret, (size_t)rez);
	free(ret);
	va_end(arg);
	return ((int)rez);
}
