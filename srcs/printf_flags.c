/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:01:49 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/06 20:00:31 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	conv[] = "sSpdDioOuUxXcCeEfFgGaAnbrk"
const char	flag[] = "#0-+ '"
const char	mod[][] = {"z", "j", "ll", "l", "hh", "h", "L"}

static void	printf_parse_num(const char *start, int *i, t_flag *flags)
{
	int	tmp;

	tmp = ft_atoi(start + *i);
	while (isdigit(start[*i]))
		(*i)++;
	if (start[*i] == '$')
	{
		flags->dollar = tmp;
		(*i)++;
	}
	else if (start[*i] == '!')
	{
		flags->system = tmp > 16 ? 0 : tmp;
		(*i)++;
	}
	else
		flags->width = tmp;
}

static int	printf_parse_mod(const char *start, int *i, t_flag *flags)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(mod[i], start[*i], ft_strlen(mod[i])))
		{
			flags->modif[i] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	printf_parse_conv(const char *start, int *i, t_flag *flags)
{
	char	*tmp;

	tmp = ft_strchr(conv, *(start + *i));
	if (!tmp)
		return (0);
	flags->conv = *tmp;
	return (1);
}

static void	printf_parse_prec(const char *start, int *i, t_flag *flags)
{
	if (start[++(*i)] == '*')
		flags->prec = va_args(*arg, int);
	else if (ft_isdigit(start[*i]))
	{
		flags->prec = ft_atoi(start + *i);
		while (ft_isdigit(start[*i]))
			(*i)++;
	}
}

/*
** Parses flags
*/

t_flag			pritnf_parse_flags(const char *start, va_list *arg, int *i)
{
	int		tmp;
	t_flag	flags;

	ft_bzero(&flags, sizeof(t_flag));
	while (!printf_parse_conv(start, i))
	{
		if (ft_strchr(flag, start[*i]))
			*((char *)flags + ft_strchr(flag, start[*(i++)]) - flag) = 1;
		else if (isdigit(start[*i]))
			printf_parse_num(start, i, &flags);
		else if (start[*i] == '*')
			flags.width = va_args(*arg, int);
		else if (start[*i] == '.')
			printf_parse_prec(start, i, &flags);
		else if (!printf_parse_mod(start, i, &flags))
		{
			flags.conv = 'c';
			break ;
		}
	}
	return (flags);
}
