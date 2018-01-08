/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 14:28:43 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/08 12:16:20 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Combines all the content from the list to one string and returns it.
*/

#include "ft_printf.h"

ssize_t	printf_lsttostr(t_list *head, char **ret)
{
	t_list	*temp;
	size_t	size;

	temp = head;
	size = 0;
	while (temp)
	{
		size += ft_strlen((char *)temp->content);
		temp = temp->next;
	}
	if (!(*ret = malloc(sizeof(char) * size + 1)))
		return (0);
	**ret = '\0';
	while (head)
	{
		ft_strcat(*ret, (char *)head->content);
		head = head->next;
	}
	return ((ssize_t)size);
}

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

t_list	*printf_lstnew(void *content, size_t content_size)
{
	t_list	*rez;

	rez = malloc(sizeof(t_list));
	if (!rez)
		return (NULL);
	rez->content = (void *)content;
	rez->next = NULL;
	rez->content_size = content_size;
	return (rez);
}
