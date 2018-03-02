/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_process_conv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:48:58 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/01 16:24:10 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_par	pull_things(t_flag *flag, t_par *params, size_t *c)
{
	if (flag->width == -1)
	{
		flag->width = (int)params[flag->wast ? flag->wast - 1 : (*c)++].i;
		if ((int)(flag->width) < 0)
		{
			flag->width= (int)(flag->width) * -1;
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
		return ((t_par)(uintmax_t)flag->err);
	if (flag->doll)
		return (params[flag->doll - 1]);
	else
		return (params[(*c)++]);
}

static char		check_neg(t_par *n, t_flag flag)
{
	t_par	tmp;

	// Add floats
	if (ft_strsrch("idD", flag.conv) != -1)
	{
		if (flag.modif[0] || flag.modif[1] || flag.modif[2] || flag.modif[3] || flag.modif[4])
			tmp.i = (ssize_t)n->i == (ssize_t)0x8000000000000000 ? 0x8000000000000000 : (uintmax_t)-(ssize_t)n->i;
		else if (flag.modif[5])
			tmp.i = n->i == 0x80 ? 0x80 : (uintmax_t)-n->i;
		else if (flag.modif[6])
			tmp.i = n->i == 0x8000 ? 0x8000 : (uintmax_t)-n->i;
		else
			tmp.i = n->i == 0x80000000 ? 0x80000000 : (uintmax_t)-n->i;
		if ((intmax_t)tmp.i > 0 || tmp.i == 0x8000000000000000)
		{
			n->i = tmp.i;
			return (1);
		}
	}
	return (0);
}

/*
** Returns len for atoi_base, width of number with all minuses, hashes and
** stuff, and total width.
*/

static void		get_size(intmax_t *sizes, t_par n, t_flag flag, char neg)
{
	// Make array of functions
	if (ft_strsrch("idDuUoOxXp", flag.conv) != -1)
		printf_int_get_size(sizes, n.i, flag);
	else if (ft_strsrch("cC", flag.conv) != -1)
		sizes[0] = printf_char_get_size((wchar_t)n.i, flag);
	else //sS
		printf_str_get_size(sizes, (int *)n.p, flag);
    if ((flag.hash && ((flag.system == 16 && n.i) || (flag.system == 8 && (flag.prec == -2 || sizes[0] >= flag.prec) && (n.i || !sizes[0])))) || flag.conv == 'p')
        sizes[2] = flag.system == 8 ? 1 : 2;
	if (ft_strsrch("dDi", flag.conv) != -1 && (neg || flag.plus || flag.space))
        sizes[3]++;
	if (flag.prec == -2 || flag.prec - sizes[0] <= 0 || ft_strsrch("idDuUoOxX", flag.conv) == -1)
		sizes[4] = 0;
	else
		sizes[4] = flag.prec - sizes[0];
	sizes[5] = flag.width - (sizes[2] + sizes[3] + sizes[4] + sizes[0]);
	if (sizes[5] < 0)
		sizes[5] = 0;
	if (flag.zero && (flag.prec == -2 || ft_strsrch("idDuUoOxX", flag.conv) == -1) && !flag.minus)
	{
		sizes[4] += sizes[5];
		sizes[5] = 0;
	}
	sizes[6] = sizes[0] + sizes[2] + sizes[3] + sizes[4] + sizes[5];
}

static char		*put_stuff(char *str, intmax_t *sizes, t_flag flag, char neg)
{
	if (sizes[5])
	{
		if (!flag.minus)
			while (sizes[5]--)
				*str++ = ' ';
		else
			while (sizes[5])
				*(str + sizes[0] + sizes[2] + sizes[3] + sizes[4] + --sizes[5]) = ' ';
	}
	// Add floats
	if (ft_strsrch("dDi", flag.conv) != -1)
	{
		if (neg)
			*str++ = '-';
		else if (flag.plus)
			*str++ = '+';
		else if (flag.space)
			*str++ = ' ';
	}
	if (sizes[2])
	{
		*str++ = '0';
		if (flag.system == 16 || flag.conv == 'p')
			*str++ = flag.conv == 'X' ? 'X' : 'x';
	}
	while (sizes[4]--)
		*str++ = '0';
	return (str);
}

static char		general(t_list *lst, t_par *params, size_t *c) //For p, d, D, i, o, O, u, U, x, X, b
{
	/*
	 ** sizes[0] == size of num (with apostrophes), of string or char
	 ** sizes[1] == biggest num of the form of 10^n, which this num can be
	 ** divided in.
	 ** sizes[2] == size of hashes
	 ** sizes[3] == minuses
	 ** sizes[4] == pure precision
	 ** sizes[5] == pure width
	 ** sizes[6] == total width
	 ** */
	intmax_t	sizes[7];
	char		neg;
	t_flag		flag;
	t_par		num;
	char		*str;
	char		*tmp;

	ft_bzero(sizes, sizeof(intmax_t) * 7);
	flag = *(t_flag *)lst->content;
	if (flag.err == -1)
	{
		free(lst->content);
		if (!(str = ft_strdup("")))
			return (0);
		lst->content = str;
		return (1);
	}
	num = pull_things(&flag, params, c);
	neg = check_neg(&num, flag);
	get_size(sizes, num, flag, neg);
	if (!(str = malloc(sizeof(char) * (size_t)(sizes[6]) + 1)))
		return (0);
	str[sizes[6]] = '\0';
	tmp = put_stuff(str, sizes, flag, neg);
	if (ft_strsrch("idDuUoOxXp", flag.conv) != -1)
		printf_int_itoa_base(num.i, tmp, flag, sizes);
	else if (ft_strsrch("cC", flag.conv) != -1)
		printf_char(&tmp, (unsigned char *)&num.i, flag);
	else //sS
		print_str(&tmp, num.p, sizes, flag);
	free(lst->content);
	lst->content = str;
	lst->content_size = (size_t)sizes[6];
	return (1);
}

static	const t_funcs	funcs[5] = {
	{"idDuUxXoOpcCbsS", &general}
/* , */
/* 	{"eEfFgGaA", &printf_float}, */
/* 	{"sSr", &printf_string}, */
/* 	{"n", &printf_pointer} */
};

// Count amount of characters for n
char	printf_process_conv(t_list *head, t_par *params)
{
	char	conv;
	size_t	c;
	int		i;

	c = 0;
	while (head)
	{
		if (!head->content_size)
		{
			conv = ((t_flag *)head->content)->conv;
			i = 0;
			while (i < 1)
				if (ft_strsrch(funcs[i].str, conv) != -1)
				{
					funcs[i].f(head, params, &c);
					break;
				}
				else
					i++;
		}
		head = head->next;
	}
	return (1);
}
