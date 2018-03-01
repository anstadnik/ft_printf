/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:47:20 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/01 12:39:02 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	printf_char_get_size(wchar_t c, t_flag flag)
{
	if (flag.modif[4] && MB_CUR_MAX > 1)
	{
		if (c > 0xffff)
			return(4);
		else if (c > 0x7ff)
			return(3);
		else if (c > 0x7f)
			return(2);
		else
			return(1);
	}
	else
		return(1);
}

char	printf_char(char **str, unsigned char *c, t_flag flag)
{
	char	ret;
	char	size;

	size = printf_char_get_size(*(wchar_t *)c, flag);
	ret = size;
	if (size == 4 && size--)
		*(*str)++ = (char)(0xf0 | c[2] >> 3);
	else if (size == 3 && size--)
		*(*str)++ = (char)(0xe0 | c[1] >> 4);
	else if (size == 2 && size--)
		*(*str)++ = (char)(0xc0 | ((c[1] & 0x7) << 2) | c[0] >> 6);
	else if (size == 1 && size--)
		*(*str)++ = (char)c[0];
	if (size == 3 && size--)
		*(*str)++ = (char)(0x80 | ((c[2] & 0x3) << 4) | (c[1] >> 4));
	if (size == 2 && size--)
		*(*str)++ = (char)(0x80 | ((c[1] & 0xf) << 2) | c[0] >> 6);
	if (size == 1 && size--)
		*(*str)++ = (char)(0x80 | (c[0] & 0x3f));
	return (ret);
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
