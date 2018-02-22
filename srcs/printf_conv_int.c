/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 11:24:46 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/22 23:14:40 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	pull_things(t_flag flag, t_par *params, size_t *c)
{
	if (flag.width == -1)
		flag.width = (int)params[flag.wast ? (*c)++ : flag.wast].i;
	if (flag.prec == -1)
		flag.prec = (int)params[flag.past ? (*c)++ : flag.past].i;
	if (flag.doll)
		return (params[flag.doll].i);
	else
		return (params[(*c)++].i);
}

/*
** Returns len for atoi_base, width of number with all minuses, hashes and
** stuff, and total width.
*/

static void		get_size(intmax_t *sizes, uintmax_t n, t_flag flag, char neg)
{
	sizes[0] = 1;
	sizes[1] = 1;
	if (n == 0 && flag.prec == 0)
		sizes[0] = 0;
	else
	{
		while (n / ((uintmax_t)sizes[1] * flag.system))
		{
			sizes[0]++;
			sizes[1] = (intmax_t)((uintmax_t)sizes[1] * flag.system);
			uintmax_t temp = (uintmax_t)sizes[1];
			temp = temp + 1;
		}
		if (flag.apostrophe)
			sizes[0] += (sizes[0] - 1) / 3;
	}
    if ((flag.hash && ((flag.system == 16 && n) || (flag.system == 8 && (flag.prec == -2 || sizes[0] >= flag.prec) && (n || !sizes[0])))) || flag.conv == 'p')
        sizes[2] = flag.system == 8 ? 1 : 2;
	if (ft_strsrch("dDi", flag.conv) != -1 && (neg || flag.plus || flag.space))
        sizes[3]++;
	if (flag.prec == -2 || flag.prec - sizes[0] <= 0)
		sizes[4] = 0;
	else
		sizes[4] = flag.prec - sizes[0];
	sizes[5] = flag.width - (sizes[2] + sizes[3] + sizes[4] + sizes[0]);
	if (sizes[5] < 0)
		sizes[5] = 0;
	if (flag.zero && flag.prec == -2 && !flag.minus)
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

static void			itoa_base(uintmax_t n, char *str, t_flag flag, intmax_t *sizes)
{
	char		*base;
	uintmax_t	size;

	if (!sizes[0])
		return ;
	size = (uintmax_t)sizes[1];
	base = flag.conv == 'X' ?  "0123456789ABCDEF" : "0123456789abcdef";
	while (size)
	{
		*(str++) = base[(n / (uintmax_t)size)];
		if ((flag.apostrophe && size > 3 * flag.system) &&
				!((size_t)(size % (3 * flag.system))) && MB_CUR_MAX > 0)
			*str++ = ',';//change this
		n %= (uintmax_t)size;
		size /= (uintmax_t)flag.system;
	}
}

/*
** Gets current node, array of params and current counter of params
** Returns 1 at error;
*/

static char		check_neg(uintmax_t *n, t_flag flag)
{
	intmax_t	tmp;

	if (ft_strsrch("idD", flag.conv) == -1)
		return (0);
	if (flag.modif[0])
		tmp = -(ssize_t)*n;
	else if (flag.modif[1])
		tmp = -(intmax_t)*n;
	else if (flag.modif[2])
		tmp = -(long long)*n;
	else if (flag.modif[3])
		tmp = -(long)*n;
	else if (flag.modif[4])
		tmp = -(short)*n;
	else if (flag.modif[5])
		tmp = -(char)*n;
	else
		//change rest like this one
		tmp = -(*(int *)n) == *(int *)n && *(int *)n ? 2147483648 : -(*(int *)n);
	if (tmp > 0)
	{
		*n = (uintmax_t)tmp;
		return (1);
	}
	return (0);
}

char		printf_conv_int(t_list *lst, t_par *params, size_t *c) //For p, d, D, i, o, O, u, U, x, X, b
{
	/*
	 ** sizes[0] == size of num (with apostrophes)
	 ** sizes[1] == biggest num of the form of 10^n, which this num can be
	 ** divided in.
	 ** sizes[2] == size of hashes, minuses and stuff
	 ** sizes[3] == minuses
	 ** sizes[4] == pure precision
	 ** sizes[5] == pure width
	 ** sizes[6] == total width
	 ** */
	intmax_t	sizes[7];
	char		neg;
	t_flag		flag;
	uintmax_t	num;// my number
	char		*str;

	ft_bzero(sizes, sizeof(intmax_t) * 6);
	flag = *(t_flag *)lst->content;
	num = pull_things(flag, params, c);
	neg = check_neg(&num, flag);
	get_size(sizes, num, flag, neg);
	if (!(str = malloc(sizeof(char) * (size_t)(sizes[6]))))
		return (0);
	str[sizes[6]] = '\0';
//	str = ;
	itoa_base(num, put_stuff(str, sizes, flag, neg), flag, sizes);
	free(lst->content);
	lst->content = str;
	lst->content_size = (size_t)sizes[6];
	return (1);
}
