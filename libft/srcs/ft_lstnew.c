/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 13:58:03 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:13:44 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a “fresh” link. The
** variables content and content_size of the new link are initialized
** by copy of the parameters of the function. If the parameter
** content is nul, the variable content is initialized to
** NULL and the variable content_size is initialized to 0 even
** if the parameter content_size isn’t. The variable next is
** initialized to NULL. If the allocation fails, the function returns
** NULL.
*/

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*rez;

	rez = malloc(sizeof(t_list));
	if (!rez || (!content_size && content))
		return (NULL);
	if (content)
	{
		rez->content = malloc(content_size);
		if (!rez->content)
		{
			free(rez);
			return (NULL);
		}
		ft_memcpy(rez->content, content, content_size);
	}
	else
		rez->content = NULL;
	rez->next = NULL;
	rez->content_size = rez->content ? content_size : 0;
	return (rez);
}
