/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:42:07 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 19:41:35 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns 1 if c is a digit or a letter.  The value of the argument must be
** representable as an unsigned char or the value of EOF.
*/

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}
