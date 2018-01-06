/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:01:49 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/06 18:23:42 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	conv[] = "sSpdDioOuUxXcCeEfFgGaAnbrk"
const char	flag[] = "#0-+ '"
const char	mod[][] = {"z", "j", "ll", "l", "hh", "h", "L"}

static int	printf_parse_flags(const char *start, int *i, t_flag *flags)
{
	if ft_strchr(flag, start[*i])
	{
		*((unsigned char *)flags + ft_strchr(flag, start[*(i++)]) - flag) = 1;
		return (1);
	}
	return (0);
}

static void	printf_parse_num(const char *start, int *i, t_flag *flags)
{
	int	tmp;

	tmp = ft_atoi(start + *i);
	while (isdigit(start[*i]))
		(*i)++;
	if (start[*i] == '$')
	{
		flags.dollar = tmp;
		(*i)++;
	}
	else if (start[*i] == '!')
	{
		flags.system = tmp > 16 ? 0 : tmp;
		(*i)++;
	}
	else
		flags.width = tmp;
}

static int	printf_parse_mod(const char *start, int *i, t_flag *flags)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(mod[i], start[*i], ft_strlen(mod[i])))
		{
			flags.modif[i] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Parses flags
*/

t_flag			pritnf_parse_flags(const char *start, va_list *arg,
		va_list arg_beg, int *i)
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
		{
			if (ft_isdigit(start[(*i)++]))
			{
				flags.width = printf_get_arg(ft_atoi(start + *i), arg_beg, );
				while (ft_isdigit(start[*i]));
			}
			else
				flags.width = va_args(*arg, int);
		}
		else if (!printf_parse_mod(start, i, &flags))
		{
			flags.conv = 'c';
			break ;
		}

	}
	return (flags);
}
