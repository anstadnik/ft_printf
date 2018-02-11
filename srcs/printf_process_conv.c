/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_process_conv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:48:58 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/02 19:26:04 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	printf_process_conv(t_list *head, t_par *params)
{
	t_flag	flag;
	size_t	c;

	c = 0;

	while (head)
	{
		if (!head->content_size)
		{
			flag = *(t_flag *)head->content;
			if (ft_strsrch("idDuUxXp", flag.conv))
				printf_int(head, params, &c); //For p, d, D, i, o, O, u, U, x, X, b
			/* else if (ft_strsrch("eEfFgGaA", flag.conv)) */
			/* 	printf_float(head, params->f); //For e, E, f, F, g, G, a, A */
			/* else if (ft_strsrch("sSr", flag.conv)) */
			/* 	printf_string(head, params->p); //For s, S, maybe r */
			/* else if (ft_strsrch("cC", flag.conv)) */
			/* 	printf_char(head, params->i); //For c, C */
			/* else if (ft_strsrch("n", flag.conv)) */
			/* 	pritnf_pointer(head, params->p); //For n */
//				printf_time(head, params->); //For time maybe
//		int	printf_flags_show(t_flag flags);


		}
		head = head->next;
	}
	return (1);
}
