/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_process_conv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:48:58 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/16 16:58:52 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	const t_funcs	funcs[5] = {
	{"idDuUxXoOp", &printf_conv_int},
	{"cC", &printf_conv_char}};
/* , */
/* 	{"eEfFgGaA", &printf_float}, */
/* 	{"sSr", &printf_string}, */
/* 	{"n", &printf_pointer} */
/* }; */

// Count amount of characters for n
char	printf_process_conv(t_list *head, t_par *params)
{
	char	conv;
	size_t	c;
	int		i;

	c = 0;
	while (head)
	{
		if (!head->content_size)
		{
			conv = ((t_flag *)head->content)->conv;
			i = 0;
			if (((t_flag *)head->content)->err)
				printf_conv_char(head, NULL, 0);
			else
				while (i < 5)
					if (ft_strsrch(funcs[i].str, conv) != -1)
					{
						funcs[i].f(head, params, &c);
						break;
					}
					else
						i++;
		}
		head = head->next;
	}
	return (1);
}
