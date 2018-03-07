/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flags_hand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:35:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/07 16:09:37 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_printf_funcs	g_arr[6] = {
	{"idDuUoOxXpb", &printf_int_size, &printf_int_write},
	{"cC", &printf_char_size, &printf_char_write},
	{"sS", &printf_str_size, &printf_str_write},
	{"k", &printf_time_size, &printf_time_write},
	{"r", &printf_row_str_size, &printf_row_str_write},
	{"q", &printf_caesar_size, &printf_caesar_write}
};

static t_printf_par	pull_things(t_printf_flags *flag, t_printf_par *params,
		size_t *c)
{
	if (flag->width == -1)
	{
		flag->width = (int)params[flag->wast ? flag->wast - 1 : (*c)++].i;
		if ((int)(flag->width) < 0)
		{
			flag->width = (int)(flag->width) * -1;
			flag->minus = 1;
		}
	}
	if (flag->prec == -1)
	{
		flag->prec = (int)params[flag->past ? flag->past - 1 : (*c)++].i;
		if ((int)(flag->prec) < 0)
			flag->prec = -2;
	}
	if (flag->err)
		return ((t_printf_par)(uintmax_t)flag->err);
	if (flag->doll)
		return (params[flag->doll - 1]);
	else
		return (params[(*c)++]);
}

static char			check_neg(t_printf_par *n, t_printf_flags flag)
{
	uintmax_t	tmp;

	if (ft_strsrch("idD", flag.conv) != -1)
	{
		if (flag.modif[0] || flag.modif[1] || flag.modif[2] || flag.modif[3] ||
				flag.modif[4])
			tmp = (intmax_t)n->i == (intmax_t)0x8000000000000000 ?
				0x8000000000000000 : (uintmax_t)-(intmax_t)n->i;
		else if (flag.modif[5])
			tmp = n->i == 0x80 ? 0x80 : (uintmax_t)-n->i;
		else if (flag.modif[6])
			tmp = n->i == 0x8000 ? 0x8000 : (uintmax_t)-n->i;
		else
			tmp = n->i == 0x80000000 ? 0x80000000 : (uintmax_t)-n->i;
		if ((intmax_t)tmp > 0 || tmp == 0x8000000000000000)
		{
			n->i = tmp;
			return (1);
		}
	}
	return (0);
}

static void			get_size(intmax_t *sizes, t_printf_par n,
		t_printf_flags flag)
{
	int i;

	i = -1;
	while (++i < 6)
		if (ft_strsrch(g_arr[i].s, flag.conv) != -1)
			sizes[0] = g_arr[i].printf_size(n, flag);
	if ((flag.hash && ((flag.system == 16 && n.i) || (flag.system == 8 &&
						(flag.prec == -2 || sizes[0] >= flag.prec) && (n.i ||
							!sizes[0])))) || flag.conv == 'p')
		sizes[1] = flag.system == 8 ? 1 : 2;
	if (~ft_strsrch("dDi", flag.conv) && (sizes[2] || flag.plus || flag.space))
		sizes[2]++;
	if (flag.prec > sizes[0] && ft_strsrch("idDuUoOxXp", flag.conv) != -1)
		sizes[3] = flag.prec - sizes[0];
	sizes[4] = flag.width - (sizes[1] + !!sizes[2] + sizes[3] + sizes[0]);
	if (sizes[4] < 0)
		sizes[4] = 0;
	if (flag.zero && (flag.prec == -2 ||
				ft_strsrch("idDuUoOxXp", flag.conv) == -1) && !flag.minus)
	{
		sizes[3] += sizes[4];
		sizes[4] = 0;
	}
	sizes[5] = sizes[0] + sizes[1] + !!sizes[2] + sizes[3] + sizes[4];
}

static char			*put_stuff(char *str, intmax_t *sizes, t_printf_flags flag)
{
	while (sizes[4]--)
		*(flag.minus ? (str + sizes[0] + sizes[1] + !!sizes[2] + sizes[3] +
					sizes[4]) : str++) = ' ';
	if (ft_strsrch("dDi", flag.conv) != -1)
	{
		if (sizes[2] == 2)
			*str++ = '-';
		else if (flag.plus)
			*str++ = '+';
		else if (flag.space)
			*str++ = ' ';
	}
	if (sizes[1])
	{
		*str++ = '0';
		if (flag.system == 16 || flag.conv == 'p')
			*str++ = flag.conv == 'X' ? 'X' : 'x';
	}
	while (sizes[3]--)
		*str++ = '0';
	return (str);
}

/*
** sizes[0] == size of num (with apostrophes), of string or char
** sizes[1] == size of hashes
** sizes[2] == minuses
** sizes[3] == pure precision
** sizes[4] == pure width
** sizes[5] == total width
*/

char				printf_flags_hand(t_list *lst, t_printf_par *params,
		size_t *c)
{
	intmax_t		sizes[6];
	int				i;
	t_printf_flags	flag;
	t_printf_par	par;
	char			*str;

	ft_bzero(sizes, sizeof(intmax_t) * 7);
	flag = *(t_printf_flags *)lst->content;
	free(lst->content);
	if (flag.err == -1)
		return ((lst->content = ft_strdup("")) == NULL);
	par = pull_things(&flag, params, c);
	sizes[2] = check_neg(&par, flag);
	get_size(sizes, par, flag);
	if (!(str = malloc(sizeof(char) * (size_t)(sizes[5]) + 1)))
		return (0);
	str[sizes[5]] = '\0';
	i = -1;
	while (++i < 6)
		if (ft_strsrch(g_arr[i].s, flag.conv) != -1)
			g_arr[i].printf_write(put_stuff(str, sizes, flag), par, *sizes,
					flag);
	lst->content = str;
	lst->content_size = (size_t)sizes[5];
	return (1);
}
