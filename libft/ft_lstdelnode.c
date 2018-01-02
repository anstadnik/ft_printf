/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 15:23:50 by astadnik          #+#    #+#             */
/*   Updated: 2017/12/30 13:03:27 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Searches for a node in a list, deletes it and sets it's previous's next
** pointer to it's next node. Now read it again and maybe u'll understand it)
*/

#include "libft.h"

void		ft_lstdelnode(t_list **head, t_list *targ)
{
	if (!head || !*head || !targ)
	{
		ft_putendl_fd("Hi, i am ft_lstdelnode, and i've got some NULLs", 2);
		return ;
	}
	if (*head == targ)
	{
		*head = targ->next;
		ft_lstdelone(&targ, &free);
		return ;
	}
	while (*head)
	{
		if ((*head)->next == targ)
		{
			(*head)->next = targ->next;
			ft_lstdelone(&targ, &free);
			return ;
		}
		head = &(*head)->next;
	}
}
