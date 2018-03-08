/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:41:13 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:51 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a “fresh” substring
** from the string given as argument. The substring begins at
** indexstart and is of size len. If start and len aren’t refering
** to a valid substring, the behavior is undefined. If the
** allocation fails, the function returns NULL.
*/

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*rez;

	if (!s)
		return (NULL);
	rez = (char *)malloc(len + 1);
	if (!rez)
		return (NULL);
	ft_strncpy(rez, (char *)(s + start), len);
	rez[len] = '\0';
	return (rez);
}
