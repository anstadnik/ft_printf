/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:45:21 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/06 13:27:25 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	printf_int_size(t_printf_par par, t_printf_flags flag)
{
	intmax_t	rez;

	rez = 1;
	if (par.i == 0 && flag.prec == 0)
		return (0);
	while (par.i / flag.system)
	{
		rez++;
		par.i /= flag.system;
	}
	if (flag.apostrophe && MB_CUR_MAX > 1)
		rez += (rez - 1) / 3;
	return (rez);
}

void		printf_int_write(char *str, t_printf_par par, intmax_t len,
		t_printf_flags flag)
{
	char		*base;
	intmax_t	tmp;

	if (!len)
		return ;
	tmp = len;
	base = flag.conv == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";
	while (len--)
	{
		if (flag.apostrophe && !((tmp - len) % 4) && len && MB_CUR_MAX > 0)
			str[len] = ',';
		else
		{
			str[len] = base[par.i % flag.system];
			par.i /= flag.system;
		}
	}
}
