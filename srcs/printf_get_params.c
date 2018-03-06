/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_get_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:13:05 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/06 18:27:37 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** 1  = char
** 2  = short
** 3  = int
** 4  = long
** 5  = long long
** 6  = intmax_t
** 7  = ssize_t
** 8  = wint_t
**
** 9  = unsigned char
** 10 = unsigned short
** 11 = unsigned int
** 12 = unsigned long
** 13 = unsigned long long
** 14 = uintmax_t
** 15 = size_t
**
** 16 = *void
*/

static void	printf_get_size2(t_printf_par *params, t_printf_flags cur,
		char conv, size_t *i)
{
	if (cur.modif[0] || cur.modif[1])
		params[cur.doll ? (size_t)cur.doll - 1 : (*i)++].i =
			(uintmax_t)(!~ft_strsrch("di", conv)) * 8 + 7;
	else if (cur.modif[2])
		params[cur.doll ? (size_t)cur.doll - 1 : (*i)++].i =
			(uintmax_t)(!~ft_strsrch("di", conv)) * 8 + 6;
	else if (cur.modif[3])
		params[cur.doll ? (size_t)cur.doll - 1 : (*i)++].i =
			(uintmax_t)(!~ft_strsrch("di", conv)) * 8 + 5;
	else if (cur.modif[4])
		params[cur.doll ? (size_t)cur.doll - 1 : (*i)++].i =
			(uintmax_t)(!~ft_strsrch("di", conv)) * 8 + 4;
	else if (cur.modif[6])
		params[cur.doll ? (size_t)cur.doll - 1 : (*i)++].i =
			(uintmax_t)(!~ft_strsrch("di", conv)) * 8 + 2;
	else if (cur.modif[5])
		params[cur.doll ? (size_t)cur.doll - 1 : (*i)++].i =
			(uintmax_t)(!~ft_strsrch("di", conv)) * 8 + 1;
	else
		params[cur.doll ? (size_t)cur.doll - 1 : (*i)++].i =
			(uintmax_t)(!~ft_strsrch("di", conv)) * 8 + 3;
}

static void	printf_get_size(t_printf_par *params, t_list *head)
{
	size_t			i;
	t_printf_flags	cur;
	char			conv;

	i = 0;
	while (head)
	{
		if (!head->content_size)
		{
			cur = *(t_printf_flags *)(head->content);
			conv = cur.conv;
			if (cur.width == -1)
				params[cur.wast ? (size_t)cur.wast - 1 : i++].i = 3;
			if (cur.prec == -1)
				params[cur.past ? (size_t)cur.past - 1 : i++].i = 3;
			if (!cur.err)
			{
				if (conv == 'n' || conv == 's' || conv == 'S')
					params[cur.doll ? (size_t)cur.doll - 1 : i++].i = 16;
				else
					printf_get_size2(params, cur, conv, &i);
			}
		}
		head = head->next;
	}
}

static void	printf_pull_param_2(t_printf_par *param, va_list arg)
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
	else
		param->p = va_arg(arg, void *);
}

static void	printf_pull_param(t_printf_par *param, va_list arg)
{
	if (param->i == 1)
		param->i = (uintmax_t)((char)va_arg(arg, int));
	else if (param->i == 2)
		param->i = (uintmax_t)((short)va_arg(arg, int));
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

void		printf_get_printf_params(t_printf_par *params, t_list *head,
		va_list arg, int params_amount)
{
	int i;

	i = 0;
	printf_get_size(params, head);
	while (i < params_amount)
		printf_pull_param(params + i++, arg);
}
