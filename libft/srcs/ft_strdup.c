/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:53:09 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:05 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates sufficient memory for a copy of the string s1, does the copy,
** and returns a pointer to it.  The pointer may subsequently be used as
** an argument to the function free(3).
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*rez;
	size_t	i;

	i = ft_strlen(s) + 1;
	rez = (char *)malloc(sizeof(char) * i);
	if (rez == NULL)
		return (NULL);
	while (i--)
		rez[i] = s[i];
	return (rez);
}
