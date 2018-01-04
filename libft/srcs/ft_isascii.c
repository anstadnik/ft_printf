/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:40:16 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 19:42:06 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns 1 if c is an ascii character.  The value of the argument must be
** representable as an unsigned char or the value of EOF.
*/

int	ft_isascii(int c)
{
	return (c <= 127 && c >= 0);
}
