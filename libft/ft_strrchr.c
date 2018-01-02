/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:07:44 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:32 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Locates the first occurrence of c (converted to a
** char) in the string pointed to by s.  The terminating null character is
** considered to be part of the string; therefore if c is `\0', the functions
** locate the terminating `\0'.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*rez;

	rez = NULL;
	while (1)
	{
		if (*s == (char)c)
			rez = (char *)s;
		if (*s++ == '\0')
			break ;
	}
	return (rez);
}
