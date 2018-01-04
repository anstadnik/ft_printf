/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:30:12 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:13:33 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds the element elem at the beginning of the list.
*/

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *elem)
{
	if (!alst || !elem)
		return ;
	if (*alst)
		elem->next = *alst;
	*alst = elem;
}
