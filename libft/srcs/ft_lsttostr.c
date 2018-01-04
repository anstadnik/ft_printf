/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:42:25 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/03 18:04:20 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Combines all the content from the list to one string and returns it.
*/

char	*ft_lsttostr(t_list *head)
{
	t_list	*temp;
	size_t	size;
	char	*rez;

	temp = head;
	size = 0;
	while (temp)
	{
		size += temp->content_size;
		temp = temp->next;
	}
	if (!(rez = malloc(sizeof(char) * size + 1)))
		return (0);
	rez[size] = '\0';
	while (head)
	{
		ft_strcat(rez, (char *)head->content);
		head = head->next;
	}
	return (rez);
}
