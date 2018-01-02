/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:23:47 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:40 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocate (with malloc(3)) and returns a “fresh” string ending
** with ’\0’ representing the integer n given as argument.
** Negative numbers must be supported. If the allocation fails,
** the function returns NULL.
*/

#include "libft.h"

static unsigned long	count(int n)
{
	unsigned long	rez;

	rez = n <= 0 ? 1 : 0;
	while (n)
	{
		rez++;
		n /= 10;
	}
	return (rez);
}

char					*ft_itoa(int n)
{
	char	*rez;
	size_t	i;

	rez = (char *)malloc(sizeof(char) * (count(n) + 1));
	if (!rez)
		return (NULL);
	i = count(n);
	rez[i] = '\0';
	if (n == 0)
		rez[--i] = '0';
	if (n < 0)
	{
		rez[0] = '-';
		rez[--i] = -(n % 10) + '0';
		n /= -10;
	}
	while (n)
	{
		rez[--i] = n % 10 + '0';
		n /= 10;
	}
	return (rez);
}
