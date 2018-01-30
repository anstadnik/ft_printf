/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_get_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:51:36 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/30 19:37:23 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printf_get_size(t_par *params, t_list *head)
{
	size_t	i;
	t_flag	cur;

	i = 0;
	while (head)
	{
		if (!head->content_size)
		{
			cur = *(t_flag *)(head->content);
			if (cur.width < 0)
				params[-cur.width].c = 1;
			else if (cur.wast)
				params[i++].c = 1;


		}
		head = head->next;
	}
}

void		printf_get_params(t_par *params, t_list *head, va_list arg)
{
	printf_get_size(params, head);
	printf_pull_params(params, arg);
}
