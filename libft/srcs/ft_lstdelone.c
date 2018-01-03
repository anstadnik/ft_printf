/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:06:48 by astadnik          #+#    #+#             */
/*   Updated: 2017/12/30 13:01:56 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Takes as a parameter a link’s pointer address and frees the
** memory of the link’s content using the function del given as
** a parameter, then frees the link’s memory using free(3). The
** memory of next must not be freed under any circumstance.
** Finally, the pointer to the link that was just freed must be
** set to NULL (quite similar to the function ft_memdel in the
** mandatory part).
*/

#include "libft.h"

void	ft_lstdelone(t_list **aslt, void (*del)(void *))
{
	if (!aslt || !*aslt || !del)
		return ;
	del((*aslt)->content);
	free(*aslt);
	*aslt = NULL;
}
