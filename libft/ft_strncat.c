/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 22:12:48 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:00 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Append a copy of the null-terminated
** string s2 to the end of the null-terminated string s1, then add a terminat-
** ing `\0'.  The string s1 must have sufficient space to hold the result.
** Appends not more than n characters from s2, and then
** adds a terminating `\0'.
*/

#include "libft.h"

char	*ft_strncat(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	while (n-- && *s2)
		s1[i++] = *s2++;
	s1[i] = '\0';
	return (s1);
}
