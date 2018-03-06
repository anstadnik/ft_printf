/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:32:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/06 15:34:23 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_num(const char *str, size_t *i, t_printf_flags *flags)
{
	int tmp;

	tmp = ft_atoi(str + *i);
	while (ft_isdigit(str[*i]))
		(*i)++;
	if (str[*i] == '!' && (*i)++)
		flags->system = tmp > 16 ? 10 : (unsigned char)tmp;
	else if (str[*i] == '$' && (*i)++)
		flags->doll = (size_t)tmp;
	else
		flags->width = tmp;
}

static void	parse_dot_ast(const char *str, size_t *i, t_printf_flags *flags,
		int *counter)
{
	int tmp;

	(*i)++;
	if (ft_isdigit(str[*i]))
	{
		tmp = ft_atoi(str + *i);
		while (ft_isdigit(str[*i]))
			(*i)++;
		if (str[*i] == '$')
		{
			flags->prec = -1;
			flags->past = (size_t)tmp;
			(*i)++;
			if (tmp > *counter)
				(*counter) = tmp;
		}
		else
			flags->width = tmp;
	}
	else
	{
		flags->prec = -1;
		flags->past = 0;
		(*counter)++;
	}
}

static void	parse_dot(const char *str, size_t *i, t_printf_flags *flags,
		int *counter)
{
	int tmp;

	(*i)++;
	if (ft_isdigit(str[*i]))
	{
		tmp = ft_atoi(str + *i);
		while (ft_isdigit(str[*i]))
			(*i)++;
		flags->prec = tmp;
	}
	else if (str[*i] == '*')
		parse_dot_ast(str, i, flags, counter);
	else
		flags->prec = 0;
}

static void	parse_ast(const char *str, size_t *i, t_printf_flags *flags,
		int *counter)
{
	int tmp;

	if (ft_isdigit(str[++(*i)]))
	{
		tmp = ft_atoi(str + *i);
		while (ft_isdigit(str[*i]))
			(*i)++;
		if (str[*i] == '$')
		{
			flags->width = -1;
			flags->wast = (size_t)tmp;
			(*i)++;
			if (tmp > *counter)
				(*counter) = tmp;
		}
		else
			flags->width = tmp;
	}
	else
	{
		flags->width = -1;
		flags->wast = 0;
		(*counter)++;
	}
}

void		printf_parse_flag(const char *str, size_t *i, t_printf_flags *flags,
		int *counter)
{
	if (ft_isdigit(str[*i]))
		parse_num(str, i, flags);
	else if (str[*i] == '.')
		parse_dot(str, i, flags, counter);
	else if (str[*i] == '*')
		parse_ast(str, i, flags, counter);
}
