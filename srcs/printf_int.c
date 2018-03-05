/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:45:21 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/05 19:23:54 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	printf_int_size(t_par par, t_flag flag)
{
	intmax_t	rez;
	intmax_t	tens;

	rez = 1;
	tens = 1;
	if (par.i == 0 && flag.prec == 0)
		rez = 0;
	else
	{
		while ((uintmax_t)tens < ULLONG_MAX/ flag.system && par.i / ((uintmax_t)tens * flag.system))
		{
			rez++;
			tens = (intmax_t)((uintmax_t)tens * flag.system);
		}
		if (flag.apostrophe && MB_CUR_MAX > 1)
			rez += (rez - 1) / 3;
	}
	return (rez);
}

void		printf_int_write(char *str, t_par par, intmax_t len, t_flag flag)
{
	char		*base;
	intmax_t	tmp;

	if (!len)
		return ;
	tmp = len;
	base = flag.conv == 'X' ?  "0123456789ABCDEF" : "0123456789abcdef";
	while (len--)
	{
		if (len && !((tmp - len) % 4) && flag.apostrophe && MB_CUR_MAX > 0)
			str[len] = ',';//change this
		else
		{
			str[len] = base[par.i % flag.system];
			par.i /= flag.system;
		}
	}
}
