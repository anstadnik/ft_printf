/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 22:03:46 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:17:24 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Computes the length of the string s.  The strnlen() function attempts to
** the length of s, but never scans beyond the first maxlen bytes of s.
*/

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	rez;

	rez = 0;
	while (*str++)
		rez++;
	return (rez);
}
