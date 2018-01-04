/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:29:23 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:17:35 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Writes n zeroed bytes to the string s.  If n is zero, bzero() does noth-
** ing.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
