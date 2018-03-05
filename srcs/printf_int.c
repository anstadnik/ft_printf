/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:45:21 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/05 16:45:30 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		printf_int_size(intmax_t *sizes, uintmax_t n, t_flag flag)
{
	sizes[0] = 1;
	sizes[1] = 1;
	if (n == 0 && flag.prec == 0)
		sizes[0] = 0;
	else
	{
		while ((uintmax_t)sizes[1] < 18446744073709551615U / flag.system && n / ((uintmax_t)sizes[1] * flag.system))
		{
			sizes[0]++;
			sizes[1] = (intmax_t)((uintmax_t)sizes[1] * flag.system);
		}
		if (flag.apostrophe && MB_CUR_MAX > 1)
			sizes[0] += (sizes[0] - 1) / 3;
	}
}

void			printf_int_write(uintmax_t n, char *str, t_flag flag, intmax_t *sizes)
{
	char		*base;
	uintmax_t	size;

	if (!sizes[0])
		return ;
	size = (uintmax_t)sizes[1];
	base = flag.conv == 'X' ?  "0123456789ABCDEF" : "0123456789abcdef";
	while (sizes[0]--)
	{
		if (sizes[0] + 1 && !((sizes[0] + 1) % 4) && flag.apostrophe && MB_CUR_MAX > 0)
		{
			*str++ = ',';//change this
			sizes[0]--;
		}
		*(str++) = base[(n / (uintmax_t)size)];
		n %= (uintmax_t)size;
		size /= (uintmax_t)flag.system;
	}
}
