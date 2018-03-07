/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_caesar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:02:25 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/07 17:41:00 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	printf_caesar_size(t_printf_par par, t_printf_flags flag)
{
	if (flag.conv == 'q')
		return ((intmax_t)ft_strlen(par.p));
	return ((intmax_t)ft_strlen(par.p));
}

void		printf_caesar_write(char *str, t_printf_par par, intmax_t len,
		t_printf_flags flag)
{
	while (len--)
	{
		*str = *(unsigned char *)par.p++ + flag.base;
		if ((*str > 'Z' && *str < 'a') || *(unsigned char *)str > 'z')
			*str -= 26;
		str++;
	}
}
