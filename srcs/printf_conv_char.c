/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:47:20 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/22 17:22:28 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static wchar_t	pull_things(t_flag flag, t_par *params, size_t *c)
{
	if (flag.width == -1)
		flag.width = (int)params[flag.wast ? (*c)++ : flag.wast].i;
	if (flag.prec == -1)
		flag.prec = (int)params[flag.past ? (*c)++ : flag.past].i;
	if (flag.err)
		return (flag.err);
	if (flag.modif[3])
		return ((wchar_t)params[flag.doll ? flag.doll : (*c)++].i);
	else
		return ((char)params[flag.doll ? flag.doll : (*c)++].i);
}

static void		get_size(intmax_t *sizes, wchar_t c, t_flag flag)
{
	if (flag.modif[3] && MB_CUR_MAX == 4)
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
	sizes[1] = flag.width - sizes[0];
	if (sizes[1] < 0)
		sizes[1] = 0;
	sizes[2] = sizes[0] + sizes[1];
}

static void	char_conv(char *str, char *c, intmax_t *sizes)
{
	if (sizes[0] == 4 && sizes[0]--)
		*str++ = (char)(0xf0 | (c[2] >> 3 & 0x3));
	else if (sizes[0] == 3 && sizes[0]--)
		*str++ = (char)(0xe0 | (c[1] >> 4));
	else if (sizes[0] == 2 && sizes[0]--)
		*str++ = (char)(0xc0 | ((c[1] & 0x7) << 2) | (c[0] >> 6));
	else if (sizes[0] == 1 && sizes[0]--)
		*str++ = c[0];
	if (sizes[0] == 3 && sizes[0]--)
		*str++ = (char)(0x80 | ((c[2] & 0x3) << 4) | (c[1] >> 4));
	if (sizes[0] == 2 && sizes[0]--)
		*str++ = (char)(0x80 | ((c[1] & 0xf) << 2) | (c[0] >> 6));
	if (sizes[0] == 1 && sizes[0]--)
		*str++ = (char)(0x80 | (c[0] & 0x3f));
}

char		printf_conv_char(t_list *lst, t_par *params, size_t *c) //For c, C
{
	/*
	 ** sizes[0] == size of char
	 ** sizes[1] == size of pure width
	 ** sizes[2] == total width
	 */
	intmax_t	sizes[3];
	wchar_t		chr;
	t_flag		flag;
	char		*str;
	size_t		i;

	i = 0;
	flag = *(t_flag *)lst->content;
	chr = pull_things(flag, params, c);
	get_size(sizes, chr, flag);
	if (!(str = malloc(sizeof(char) * (size_t)(sizes[2]))))
		return (0);
	if (flag.minus)
		while (sizes[1]--)
			str[i++ + (size_t)sizes[0]] = flag.zero ? '0' : ' ';
	else
		while (sizes[1]--)
			str[i++] = flag.zero ? '0' : ' ';
	if (flag.modif[3] && MB_CUR_MAX == 4)
		char_conv(flag.minus ? str : str + i, (char *)&chr, sizes);
	else
	{
		if (flag.minus)
			*str = (char)chr;
		else
			str[i] = (char)chr;
	}
	free(lst->content);
	lst->content = str;
	lst->content_size = (size_t)sizes[2];
	return (1);
}
