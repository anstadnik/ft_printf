/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:45:52 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/06 11:57:42 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	printf_str_size(t_printf_par par, t_printf_flags flag)
{
	intmax_t	rez;

	rez = 0;
	if (!par.p)
		rez = 6;
	else
		while (42)
		{
			if (flag.modif[4])
			{
				if (!*(wint_t *)par.p)
					break;
				rez += printf_char_size((t_printf_par)(uintmax_t)*(wchar_t *)par.p, flag);
				par.p += sizeof(wchar_t);
			}
			else
			{
				if (!*(char *)par.p)
					break;
				rez++;
				par.p++;
			}
			if (flag.prec != -2 && rez >= flag.prec)
				break;
		}
	if (flag.prec != -2 && rez > flag.prec)
		rez = flag.prec;
	return (rez);
}

void	print_str_write(char *str, t_printf_par par, intmax_t len, t_printf_flags flag)
{
	t_printf_par	tmp;
	char	ret;

	if (!par.p)
		ft_strncpy(str, "(null)", (size_t)len);
	else
		while (len > 0)
		{
			if (flag.modif[4])
			{
				tmp.i = (uintmax_t)*(wchar_t *)par.p;
				ret = printf_char_write(str, tmp, 0, flag);
				len -= ret;
				str += ret;
				par.p += sizeof(wchar_t);
			}
			else
			{
				*str++ = *(char *)par.p++;
				len--;
			}
		}
}
