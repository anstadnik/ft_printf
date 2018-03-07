/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_row_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 19:16:54 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/07 18:29:43 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	printf_row_str_size(t_printf_par par, t_printf_flags flag)
{
	intmax_t	rez;
	char		*str;

	rez = par.p ? 0 : 6;
	str = (char *)par.p;
	if (par.p)
		while (flag.prec == -2 || rez < flag.prec)
		{
			if (!*str)
				break ;
			if (ft_isprint(*str))
				rez++;
			else
			{
				rez++;
				if (*str < 10)
					rez++;
				else
					rez += *str < 100 ? 2 : 3;
			}
			str++;
		}
	if (flag.prec != -2 && rez > flag.prec)
		rez = flag.prec;
	return ((intmax_t)rez);
}

static void	put_stuff(char **str, intmax_t *len, char *s)
{
	int		i;
	char	n;

	i = 100;
	*(*str)++ = '\\';
	(*len)--;
	n = *s;
	while (!(n / (i / 10)))
		i /= 10;
	while ((i /= 10) && *len > 0)
	{
		(*len)--;
		*(*str)++ = n / i + '0';
		n %= i;
	}
}

void		printf_row_str_write(char *str, t_printf_par par, intmax_t len,
		t_printf_flags flag)
{
	char	*s;

	s = par.p;
	flag.err = 0;
	if (!par.p)
		ft_strncpy(str, "(null)", (size_t)len);
	else
		while (len > 0)
		{
			if (ft_isprint(*s))
			{
				len--;
				*str++ = *s;
			}
			else
				put_stuff(&str, &len, s);
			s++;
		}
}
