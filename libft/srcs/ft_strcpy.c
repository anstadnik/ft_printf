/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:58:17 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:42 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Copy the string src to dst (including
** the terminating `\0' character.)
*/

#include "libft.h"

char	*ft_strcpy(char *s1, char const *s2)
{
	size_t	i;

	i = 0;
	while (1)
	{
		s1[i] = s2[i];
		if (!s2[i])
			return (s1);
		i++;
	}
}
