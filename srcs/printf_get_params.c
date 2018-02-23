/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_get_params.i                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:51:36 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/23 22:49:01 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 1  = char */
/* 2  = short */
/* 3  = int */
/* 4  = long */
/* 5  = long long */
/* 6  = intmax_t */
/* 7  = ssize_t */
/* 8  = wint_t */

/* 9  = unsigned char */
/* 10 = unsigned short */
/* 11 = unsigned int */
/* 12 = unsigned long */
/* 13 = unsigned long long */
/* 14 = uintmax_t */
/* 15 = size_t */

/* 16 = float */
/* 17 = double */
/* 18 = long double */

/* 19 = *void */

/* static void	printf_get_size_2(t_par *params, t_flag cur, size_t i) */
/* { */
/* } */

static void	printf_get_size(t_par *params, t_list *head)
{
	size_t	i;
	t_flag	cur;
	char	conv;

	i = 0;
	while (head)
	{
		if (!head->content_size)
		{
			cur = *(t_flag *)(head->content);
			conv = cur.conv;
			if (cur.width == -1)
				params[cur.wast ? (size_t)cur.wast - 1: i++].i = 3;
			if (cur.prec == -1)
				params[cur.past ? (size_t)cur.past - 1: i++].i = 3;
			if (!cur.err)
			{
				if (conv == 'D')
					params[cur.doll ? (size_t)cur.doll - 1 : i++].i = 4;
				else if (conv == 'U' || conv == 'X')
					params[cur.doll ? (size_t)cur.doll - 1 : i++].i = 12;
				else if (conv == 'C')
					params[cur.doll ? (size_t)cur.doll - 1 : i++].i = 8;
				else if (conv == 'n' || conv == 's' || conv == 'S')
					params[cur.doll ? (size_t)cur.doll - 1 : i++].i = 19;
				else if (ft_strsrch("aAeEfFgG", conv) != -1)
				{
					if (cur.modif[6])
						params[cur.doll ? (size_t)cur.doll - 1 : i++].i = 18;
					else
						params[cur.doll ? (size_t)cur.doll - 1 : i++].i = 17;
				}
				else
				{
					if (cur.modif[0] || cur.modif[1])
						params[cur.doll ? (size_t)cur.doll - 1 : i++].i = ~ft_strsrch("di", conv) ? 7 : 15;
					else if (cur.modif[2])
						params[cur.doll ? (size_t)cur.doll - 1 : i++].i = ~ft_strsrch("di", conv) ? 6 : 14;
					else if (cur.modif[3])
						params[cur.doll ? (size_t)cur.doll - 1 : i++].i = ~ft_strsrch("di", conv) ? 5 : 13;
					else if (cur.modif[4])
						params[cur.doll ? (size_t)cur.doll - 1 : i++].i = ~ft_strsrch("di", conv) ? 4 : 12;
					else if (cur.modif[6])
						params[cur.doll ? (size_t)cur.doll - 1 : i++].i = ~ft_strsrch("di", conv) ? 2 : 10;
					else if (cur.modif[5])
						params[cur.doll ? (size_t)cur.doll - 1 : i++].i = ~ft_strsrch("di", conv) ? 1 : 9;
					else
						params[cur.doll ? (size_t)cur.doll - 1 : i++].i = ~ft_strsrch("di", conv) ? 3 : 11;
				}
			}
		}
		head = head->next;
	}
}

static void	printf_pull_param_2(t_par *param, va_list arg)
{
	if (param->i == 11)
		param->i = va_arg(arg, unsigned int);
	else if (param->i == 12)
		param->i = va_arg(arg, unsigned long);
	else if (param->i == 13)
		param->i = va_arg(arg, unsigned long long);
	else if (param->i == 14)
		param->i = va_arg(arg, uintmax_t);
	else if (param->i == 15)
		param->i = va_arg(arg, size_t);
	else if (param->i == 16)
		param->f = (float)va_arg(arg, double);
	else if (param->i == 17)
		param->f = va_arg(arg, double);
	else if (param->i == 18)
		param->f = va_arg(arg, long double);
	else
		param->p = va_arg(arg, void *);
}

static void	printf_pull_param(t_par *param, va_list arg)
{
	if (param->i == 1)
		param->i = (uintmax_t)(char)va_arg(arg, int);
	else if (param->i == 2)
		param->i = (uintmax_t)(short)va_arg(arg, int);
	else if (param->i == 3)
		param->i = (uintmax_t)va_arg(arg, int);
	else if (param->i == 4)
		param->i = (uintmax_t)va_arg(arg, long);
	else if (param->i == 5)
		param->i = (uintmax_t)va_arg(arg, long long);
	else if (param->i == 6)
		param->i = (uintmax_t)va_arg(arg, intmax_t);
	else if (param->i == 7)
		param->i = (uintmax_t)va_arg(arg, ssize_t);
	else if (param->i == 8)
		param->i = (uintmax_t)va_arg(arg, wint_t);
	else if (param->i == 9)
		param->i = (uintmax_t)(unsigned char)va_arg(arg, int);
	else if (param->i == 10)
		param->i = (uintmax_t)(unsigned short)va_arg(arg, int);
	else 
		printf_pull_param_2(param, arg);
}

/*
** Pulls params from va_list, and puts them into array.
*/

void		printf_get_params(t_par *params, t_list *head, va_list arg,
		int params_amount)
{
	int i;

	i = 0;
	/* Fills array items with 'code' which will later tell the type of the
	variable */
	printf_get_size(params, head);
	/* Actually pulls params */
	while (i < params_amount)
		printf_pull_param(params + i++, arg);
}
