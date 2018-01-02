/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:47:48 by astadnik          #+#    #+#             */
/*   Updated: 2017/12/23 15:50:16 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns an array of “fresh”
** strings (all ending with ’\0’, including the array itself) obtained
** by spliting s using the character c as a delimiter.
** If the allocation fails the function returns NULL. Example
** : ft_strsplit("*hello*fellow***students*", ’*’) returns
** the array ["hello", "fellow", "students"].
*/

#include "libft.h"

static void	f(char ***arr, size_t i)
{
	while (i--)
		free(*arr[i]);
	free(*arr);
}

static char	**fill(char const *s, char c, size_t am, char **rez)
{
	size_t	i;
	char	*beg;
	char	*end;

	i = 0;
	beg = (char *)s;
	while (i < am)
	{
		end = ft_strchr(beg, c);
		if (!end)
			end = ft_strchr(beg, '\0');
		if (end != beg || *beg == '\0')
		{
			rez[i++] = ft_strsub(beg, 0, (size_t)(end - beg));
			if (rez[i - 1] == NULL)
			{
				f(&rez, i - 1);
				return (NULL);
			}
		}
		beg = end + 1;
	}
	rez[am] = NULL;
	return (rez);
}

char		**ft_strsplit(char const *s, char c)
{
	size_t	am;
	size_t	i;
	char	**rez;

	if (!s)
		return (NULL);
	i = 0;
	am = 0;
	while (1)
	{
		if ((s[i] == '\0' || s[i] == c) && i != 0 && s[i - 1] != c)
			am++;
		if (!s[i])
			break ;
		i++;
	}
	rez = (char**)malloc(sizeof(char *) * (am + 1));
	if (!rez)
		return (NULL);
	return (fill(s, c, am, rez));
}
