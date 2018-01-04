/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:13:19 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:43 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applies the function f to each character of the string passed
** as argument by giving its index as first argument to create a
** “fresh” new string (with malloc(3)) resulting from the successive
** applications of f.
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*rez;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	rez = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!rez)
		return (NULL);
	while (s[i])
	{
		rez[i] = f(i, ((char *)s)[i]);
		i++;
	}
	rez[i] = '\0';
	return (rez);
}
