/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:01:49 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/12 15:54:36 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	g_conv[] = "sSpdDioOuUxXcCeEfFgGaAnbrk";
static const char	g_flag[] = "#0-+ '";
static const char	g_mod[7][3] = {"z", "j", "ll", "l", "hh", "h", "L"};

static int			printf_parse_conv(const char *start, int *i, t_flag *flags)
{
	char	*tmp;

	tmp = ft_strchr(g_conv, *(start + *i));
	if (!tmp)
		return (0);
	flags->conv = *tmp;
	if (flags->conv == 'o' || flags->conv == 'O')
		flags->system = 8;
	if (flags->conv == 'x' || flags->conv == 'X')
		flags->system = 16;
	(*i)++;
	return (1);
}

static void			printf_parse_num(const char *start, int *i, t_flag *flags)
{
	int	tmp;

	tmp = ft_atoi(start + *i);
	while (ft_isdigit(start[*i]))
		(*i)++;
	if (start[*i] == '!')
	{
		flags->system = tmp > 16 ? 10 : (char)tmp;
		(*i)++;
	}
	else
		flags->width = tmp;
}

static void			printf_parse_prec(const char *start, int *i, t_flag *flags,
		va_list arg)
{
	if (start[++(*i)] == '*')
	{
		flags->prec = va_arg(arg, int);
		return ;
	}
	if (ft_isdigit(start[*i]))
	{
		flags->prec = ft_atoi(start + *i);
		while (ft_isdigit(start[*i]))
			(*i)++;
	}
}

static int			printf_parse_mod(const char *start, int *i, t_flag *flags)
{
	int	j;

	j = 0;
	while (j < 7)
	{
		if (!ft_strncmp(g_mod[j], start + *i, ft_strlen(g_mod[j])))
		{
			flags->modif[j] = 1;
			*i += ft_strlen(g_mod[j]);
			return (1);
		}
		j++;
	}
	return (0);
}

/*
** Parses flags
*/

t_flag				printf_parse_flags(const char *start, va_list arg, int *i)
{
	t_flag	flags;

	ft_bzero(&flags, sizeof(t_flag));
	flags.conv = 'c';
	flags.system = 10;
	while (!printf_parse_conv(start, i, &flags))
	{
		if (ft_strchr(g_flag, start[*i]))
			*(char *)((char *)&flags + (size_t)ft_strchr(g_flag, start[(*i)++])
					- (size_t)g_flag) = 1;
		else if (ft_isdigit(start[*i]))
			printf_parse_num(start, i, &flags);
		else if (start[*i] == '*')
		{
			flags.width = va_arg(arg, int);
			(*i)++;
		}
		else if (start[*i] == '.')
			printf_parse_prec(start, i, &flags, arg);
		else if (!printf_parse_mod(start, i, &flags))
		{
			flags.err = start[(*i)++];
			break ;
		}
	}
	return (flags);
}
