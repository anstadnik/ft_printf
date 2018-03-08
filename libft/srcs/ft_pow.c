/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:53:53 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/05 14:20:37 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_pow(unsigned long long n, int p)
{
	unsigned long long	rez;

	rez = 1;
	if (!p)
		return (1);
	else if (p > 0)
		while (p--)
			rez *= n;
	else
		while (p++)
			rez /= n;
	return (rez);
}
