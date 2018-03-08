/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:15:18 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/05 14:35:19 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_log(unsigned long long n)
{
	int					rez;
	unsigned long long	tens;

	rez = 0;
	tens = 10;
	if (n == 1)
		return (0);
	while (n / tens)
	{
		rez++;
		tens *= 10;
	}
	return (rez);
}
