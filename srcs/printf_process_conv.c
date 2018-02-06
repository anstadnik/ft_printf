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


		}
		head = head->next;
	}
}
