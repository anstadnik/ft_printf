/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:36:43 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/04 19:57:28 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts a lower-case letter to the corresponding
** upper-case letter.  The argument must be representable as an unsigned char
** or the value of EOF.
*/

int	ft_toupper(int c)
{
	return ((c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c);
}
