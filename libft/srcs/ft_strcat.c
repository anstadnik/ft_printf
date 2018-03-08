/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 22:10:25 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:25 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Append a copy of the null-terminated
** string s2 to the end of the null-terminated string s1, then add a terminat-
** ing `\0'.  The string s1 must have sufficient space to hold the result.
*/

#include "libft.h"

char	*ft_strcat(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	while (1)
	{
		s1[i++] = *s2;
		if (!*s2++)
			return (s1);
	}
}
