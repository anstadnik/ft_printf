/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 22:01:26 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:12 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Copy the string src to dst (including
** the terminating `\0' character.)
*/

#include "libft.h"

char	*ft_strncpy(char *s1, char *s2, size_t len)
{
	size_t	i;

	i = 0;
	while (s2[i])
	{
		if (!len--)
			return (s1);
		s1[i] = s2[i];
		i++;
	}
	while (len--)
		s1[i++] = '\0';
	return (s1);
}
