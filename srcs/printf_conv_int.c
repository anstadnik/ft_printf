/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 11:24:46 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/12 17:38:13 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Returns len for atoi_base, width of number with all minuses, hashes and
** stuff, and total width.
*/

static uintmax_t	pull_things(t_flag flag, t_par *params, size_t *c)
{
	if (flag.width < 0)
		flag.width = (int)params[-flag.width].i;
	else if (flag.wast)
		flag.width = (int)params[(*c)++].i;
	if (flag.prec < 0)
		flag.prec = (int)params[-flag.prec].i;
	else if (flag.past)
		flag.prec = (int)params[(*c)++].i;
	if (flag.doll)
		return (params[flag.doll].i);
	else
		return (params[(*c)++].i);
}

static void		get_size(intmax_t *sizes, uintmax_t n, t_flag flag, char neg)
{
	int	system;//check later if I need this. Performance, I mean

	system = flag.system;
	sizes[0] = 1;
	sizes[1] = 1;
	while (n / (uintmax_t)(sizes[1] * system))
	{
		sizes[0]++;
		sizes[1] *= (uintmax_t)system;
	}
    if (flag.apostrophe)
        sizes[0] += (sizes[0] - 1) / 3;
    if (flag.hash && (flag.system == 16 || flag.system == 8))
        sizes[2] = flag.system == 16 ? 2 : 1;
	if (neg || flag.minus || flag.hash || flag.plus)
        sizes[2]++;
	sizes[3] = flag.prec - sizes[0];
	if (sizes[3] < 0)
		sizes[3] = 0;
	sizes[4] = flag.width - (sizes[2] + (sizes[3] ? flag.prec : sizes[0]));
	if (sizes[4] < 0)
		sizes[4] = 0;
	sizes[5] = sizes[0] + sizes[2] + sizes[3] + sizes[4];
}

static char		*put_stuff(char *str, intmax_t *sizes, t_flag flag, char neg)
{
	if (sizes[4])
	{
		if (!flag.minus)
			while (sizes[4]--)
				*str++ = ' ';
		else
			while (sizes[4])
				*(str + sizes[0] + sizes[2] + sizes[3] + sizes[4]--) = ' ';
	}
	while (sizes[3]--)
		*str++ = '0';
	if (neg)
		*str++ = '-';
	else if (flag.plus)
		*str++ = '+';
	else if (flag.space)
		*str++ = ' ';
    if (flag.hash && (flag.system == 16 || flag.system == 8))
	{
		*str++ = '0';
		if (flag.system == 16)
			*str++ = 'x';
	}
	return (str);
}

static void			itoa_base(uintmax_t n, char *str, t_flag flag, intmax_t *sizes)
{
	char	*base;
   
	base = flag.conv == 'X' ?  "0123456789ABCDEF" : "0123456789abcdef";
	while (n)
	{
		*(str++) = base[(n / (size_t)sizes[1])];
		if (flag.apostrophe && sizes[1] > (3 * flag.system) &&
				!((size_t)(sizes[1] % (3 * flag.system))) && MB_CUR_MAX > 0)
				*str++ = ',';//change this
		n %= (uintmax_t)sizes[1];
		sizes[1] /= flag.system;
	}

}

/*
** Gets current node, array of params and current counter of params
** Returns 1 at error;
*/

char		printf_int(t_list *lst, t_par *params, size_t *c) //For p, d, D, i, o, O, u, U, x, X, b
{
	/*
	 ** sizes[0] == size of num (with apostrophes)
	 ** sizes[1] == biggest num of the form of 10^n, which this num can be
	 ** divided in.
	 ** sizes[2] == size of hashes, minuses and stuff
	 ** sizes[3] == pure precision
	 ** sizes[4] == pure width
	 ** sizes[5] == total width
	 ** */
	intmax_t	sizes[6];
	char		neg;
	t_flag		flag;
	uintmax_t	num;// my number
	char		*str;

	ft_bzero(sizes, sizeof(intmax_t) * 4);
	flag = *(t_flag *)lst->content;
	num = pull_things(flag, params, c);
	if (ft_strsrch("idD", flag.conv) && (intmax_t)num < 0)
	{
		num = num << 1 >> 1;
		neg = 1;
	}
	else
		neg = 0;
	get_size(sizes, num, flag, neg);
	if (!(str = malloc(sizeof(char) * (size_t)(sizes[5]))))
		return (0);
//	str = ;
	itoa_base(num, put_stuff(str, sizes, flag, neg), flag, sizes);
	free(lst->content);
	lst->content = str;
	lst->content_size = (size_t)sizes[5];
	return (1);
}
