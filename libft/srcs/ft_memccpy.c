/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:48:31 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:03 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Copies bytes from string src to string dst.  If the character c (as
** converted to an unsigned char) occurs in the string src, the copy
** stops and a pointer to the byte after the copy of c in the string
** dst is returned.  Otherwise, n bytes are copied, and a
** NULL pointer is returned.
*/

#include "libft.h"

void	*ft_memccpy(void *s1, void const *s2, int c, size_t n)
{
	while (n--)
	{
		*(unsigned char *)s1++ = *(unsigned char *)s2;
		if (*(unsigned char *)s2 == (unsigned char)c)
			return ((void *)s1);
		else
			s2++;
	}
	return (NULL);
}
