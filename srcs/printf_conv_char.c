/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:47:20 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/28 17:00:35 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		printf_char_get_size(intmax_t *sizes, wchar_t c, t_flag flag)
{
	if (flag.modif[4] && MB_CUR_MAX > 1)
	{
		if (c > 0xffff)
			sizes[0] = 4;
		else if (c > 0x7ff)
			sizes[0] = 3;
		else if (c > 0x7f)
			sizes[0] = 2;
		else
			sizes[0] = 1;
	}
	else
		sizes[0] = 1;
}

void	printf_char(char *str, char *c, intmax_t *sizes)
{
	if (sizes[0] == 4 && sizes[0]--)
		*str++ = (char)(0xf0 | (c[2] >> 3 & 0x3));
	else if (sizes[0] == 3 && sizes[0]--)
		*str++ = (char)(0xe0 | (c[1] >> 4));
	else if (sizes[0] == 2 && sizes[0]--)
		*str++ = (char)(0xc0 | ((c[1] & 0x7) << 2) | (c[0] >> 6 & 0x3));
	else if (sizes[0] == 1 && sizes[0]--)
		*str++ = c[0];
	if (sizes[0] == 3 && sizes[0]--)
		*str++ = (char)(0x80 | ((c[2] & 0x3) << 4) | (c[1] >> 4));
	if (sizes[0] == 2 && sizes[0]--)
		*str++ = (char)(0x80 | ((c[1] & 0xf) << 2) | (c[0] >> 6));
	if (sizes[0] == 1 && sizes[0]--)
		*str++ = (char)(0x80 | (c[0] & 0x3f));
}

/*char		printf_char() //For c, C*/
/*{*/
	/*
	 ** sizes[0] == size of char
	 ** sizes[1] == size of pure width
	 ** sizes[2] == total width
	 */
/*	intmax_t	sizes[3];*/
/*	wchar_t		chr;*/
/*	t_flag		flag;*/
/*	char		*str;*/
/*	size_t		i;*/

/*	i = 0;*/
/*	flag = *(t_flag *)lst->content;*/
/*	chr = pull_things(flag, params, c);*/
/*	get_size(sizes, chr, flag);*/
/*	if (!(str = malloc(sizeof(char) * (size_t)(sizes[2]))))*/
/*		return (0);*/
/*	if (flag.minus)*/
/*		while (sizes[1]--)*/
/*			str[i++ + (size_t)sizes[0]] = flag.zero ? '0' : ' ';*/
/*	else*/
/*		while (sizes[1]--)*/
/*			str[i++] = flag.zero ? '0' : ' ';*/
/*	if (flag.modif[3] && MB_CUR_MAX == 4)*/
/*		char_conv(flag.minus ? str : str + i, (char *)&chr, sizes);*/
/*	else*/
/*	{*/
/*		if (flag.minus)*/
/*			*str = (char)chr;*/
/*		else*/
/*			str[i] = (char)chr;*/
/*	}*/
/*	free(lst->content);*/
/*	lst->content = str;*/
/*	lst->content_size = (size_t)sizes[2];*/
/*	return (1);*/
/*}*/
