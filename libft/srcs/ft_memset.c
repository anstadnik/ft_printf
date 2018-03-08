/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:26:35 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:28 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Writes len bytes of value c (converted to an unsigned char) to the
** string b.
*/

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char q;

	q = (unsigned char)c;
	while (n--)
		((unsigned char *)str)[n] = q;
	return (str);
}
