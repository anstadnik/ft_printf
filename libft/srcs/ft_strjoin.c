/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:49:48 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:26 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a “fresh” string ending
** with ’\0’, result of the concatenation of s1 and s2. If
** the allocation fails the function returns NULL.
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rez;

	if (!s1 || !s2)
		return (0);
	rez = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!rez)
		return (NULL);
	return (ft_strcat(ft_strcpy(rez, s1), (char*)s2));
}
