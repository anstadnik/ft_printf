/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:26:43 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/06 11:41:37 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The atoi() function converts the initial portion of the string pointed to by
** str to int representation.
*/

#include "libft.h"

int	ft_atoi(const char *s)
{
	char				neg;
	unsigned long long	rez;

	rez = 0;
	neg = 0;
	while (ft_iswhitespace(*s))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			neg = 1;
	while (*s == '0')
		s++;
	while (ft_isdigit(*s))
	{
		rez = rez * 10 + (unsigned long long)(*s++ - '0');
		if (rez > 2147483647 || (rez > 2147483648 && neg))
			return (neg ? 2147483647 :  -2147483648);
	}
	return (neg ? -1 * (int)rez : (int)rez);
}
