/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:46:31 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/06 13:17:23 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	printf_char_size(t_printf_par par, t_printf_flags flag)
{
	if (flag.modif[4] && MB_CUR_MAX > 1)
	{
		if (par.i > 0xffff)
			return (4);
		else if (par.i > 0x7ff)
			return (3);
		else if (par.i > 0x7f)
			return (2);
		else
			return (1);
	}
	else
		return (1);
}

void		printf_char_write(char *str, t_printf_par par, intmax_t len,
		t_printf_flags flag)
{
	char			size;
	unsigned char	*c;

	c = (unsigned char *)&par.i;
	size = len ? (char)len : (char)printf_char_size(par, flag);
	if (!flag.modif[4])
	{
		*str = (char)par.i;
		return ;
	}
	if (size == 4 && size--)
		*str++ = (char)(0xf0 | c[2] >> 3);
	else if (size == 3 && size--)
		*str++ = (char)(0xe0 | c[1] >> 4);
	else if (size == 2 && size--)
		*str++ = (char)(0xc0 | ((c[1] & 0x7) << 2) | c[0] >> 6);
	else if (size == 1 && size--)
		*str++ = (char)c[0];
	if (size == 3 && size--)
		*str++ = (char)(0x80 | ((c[2] & 0x3) << 4) | (c[1] >> 4));
	if (size == 2 && size--)
		*str++ = (char)(0x80 | ((c[1] & 0xf) << 2) | c[0] >> 6);
	if (size == 1 && size--)
		*str++ = (char)(0x80 | (c[0] & 0x3f));
}
