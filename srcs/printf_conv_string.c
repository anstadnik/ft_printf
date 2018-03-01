/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:41:03 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/01 12:37:48 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		printf_str_get_size(intmax_t *sizes, void *p, t_flag flag)
{
	if (!p)
		sizes[0] = 6;
	else
		while (42)
		{
			if (flag.modif[4])
			{
				if (!*(wint_t *)p)
					break;
				sizes[0] += printf_char_get_size(*(wint_t *)p, flag);
				p += sizeof(wchar_t);
			}
			else
			{
				if (!*(char *)p)
					break;
				sizes[0]++;
				p++;
			}
			if (flag.prec != -2 && sizes[0] >= flag.prec)
				break;
		}
	if (flag.prec != -2 && sizes[0] > flag.prec)
		sizes[0] = flag.prec;
}

void	print_str(char **str, void *p, intmax_t *sizes, t_flag flag)
{
	if (!p)
		ft_strncpy(*str, "(null)", (size_t)sizes[0]);
	else
		while (sizes[0])
		{
			if (flag.modif[4])
			{
				sizes[0] -= printf_char(str, (unsigned char *)p, flag);
				p += sizeof(wchar_t);
			}
			else
			{
				*(*str)++ = *(char *)p++;
				sizes[0]--;
			}
		}
}
