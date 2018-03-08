/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsrch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:49:45 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/16 15:27:39 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Searches for a character in the string, and returns it's index if it's
** founded, or 0 otherwise.
*/

ssize_t	ft_strsrch(const char *str, char c)
{
	ssize_t	rez;

	if (!str)
		return (-1);
	rez = 0;
	while (str[rez])
		if (str[rez] == c)
			return (rez);
		else
			rez++;
	return (-1);
}
