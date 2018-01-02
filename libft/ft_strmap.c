/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:10:12 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:16:03 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applies the function f to each character of the string given
** as argument to create a “fresh” new string (with malloc(3))
** resulting from the successive applications of f.
*/

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char		*rez;
	size_t		i;

	if (!s || !f)
		return (NULL);
	i = 0;
	rez = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!rez)
		return (NULL);
	while (s[i])
	{
		rez[i] = f(s[i]);
		i++;
	}
	rez[i] = '\0';
	return (rez);
}
