/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 18:36:19 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/07 17:42:08 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	printf_time_size(t_printf_par par, t_printf_flags flag)
{
	if (par.i && flag.conv == 'k')
		return (25);
	return (25);
}

void		printf_time_write(char *str, t_printf_par par, intmax_t len,
		t_printf_flags flag)
{
	if (flag.conv == 'k')
		ft_strncpy(str, ctime((time_t *)&par.i), (size_t)len);
}
