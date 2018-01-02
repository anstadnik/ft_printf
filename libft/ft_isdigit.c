/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:41:10 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 19:42:19 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns 1 if c is a digit.  The value of the argument must be
** representable as an unsigned char or the value of EOF.
*/

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
