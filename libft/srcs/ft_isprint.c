/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:38:16 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 19:42:34 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns 1 if c is printable.  The value of the argument must be
** representable as an unsigned char or the value of EOF.
*/

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
