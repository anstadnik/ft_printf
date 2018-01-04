/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 18:43:26 by astadnik          #+#    #+#             */
/*   Updated: 2017/12/25 19:14:44 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Creates a new allocation, copies as much of the old data pointed to by ptr
** as will fit to the new allocation(smaller from size_src and size), frees
** the old allocation, and returns a pointer to the allocated memory.
*/

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size_src, size_t size)
{
	void	*rez;

	if (!(rez = malloc(size)))
	{
		ft_putendl_fd("Help... Help... Ft_realloc needs some help", 2);
		return (NULL);
	}
	if (ptr)
	{
		ft_memcpy(rez, ptr, size_src > size - 1 ? size - 1 : size_src);
		free(ptr);
	}
	return (rez);
}
