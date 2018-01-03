/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:10:45 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:13:16 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds the element new at the end of the list.
*/

#include "libft.h"

void	ft_lstaddb(t_list **head, t_list *list)
{
	if (!head)
		return ;
	while (*head)
		head = &((*head)->next);
	*head = list;
}
