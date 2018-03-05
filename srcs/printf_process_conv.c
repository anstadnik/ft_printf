/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_process_conv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:48:58 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/05 19:27:40 by astadnik         ###   ########.fr       */
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

	if (ft_strsrch("idD", flag.conv) != -1)
	{
		if (flag.modif[0] || flag.modif[1] || flag.modif[2] || flag.modif[3] || flag.modif[4])
			tmp.i = (intmax_t)n->i == (intmax_t)0x8000000000000000 ? 0x8000000000000000 : (uintmax_t)-(intmax_t)n->i;
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
	if (ft_strsrch("idDuUoOxXpb", flag.conv) != -1)
		sizes[0] = printf_int_size(n, flag);
	else if (ft_strsrch("cC", flag.conv) != -1)
		sizes[0] = printf_char_size((wchar_t)n.i, flag);
	else //sS
		printf_str_size(sizes, (int *)n.p, flag);
    if ((flag.hash && ((flag.system == 16 && n.i) || (flag.system == 8 && (flag.prec == -2 || sizes[0] >= flag.prec) && (n.i || !sizes[0])))) || flag.conv == 'p')
        sizes[1] = flag.system == 8 ? 1 : 2;
	if (ft_strsrch("dDi", flag.conv) != -1 && (neg || flag.plus || flag.space))
        sizes[2]++;
	if (flag.prec == -2 || flag.prec - sizes[0] <= 0 || ft_strsrch("idDuUoOxXp", flag.conv) == -1)
		sizes[3] = 0;
	else
		sizes[3] = flag.prec - sizes[0];
	sizes[4] = flag.width - (sizes[1] + sizes[2] + sizes[3] + sizes[0]);
	if (sizes[4] < 0)
		sizes[4] = 0;
	if (flag.zero && (flag.prec == -2 || ft_strsrch("idDuUoOxXp", flag.conv) == -1) && !flag.minus)
	{
		sizes[3] += sizes[4];
		sizes[4] = 0;
	}
	sizes[5] = sizes[0] + sizes[1] + sizes[2] + sizes[3] + sizes[4];
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
				*(str + sizes[0] + sizes[1] + sizes[2] + sizes[3] + --sizes[4]) = ' ';
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

static char		printf_flags_hand(t_list *lst, t_par *params, size_t *c)
{
	/*
	 ** sizes[0] == size of num (with apostrophes), of string or char
	 ** sizes[1] == size of hashes
	 ** sizes[2] == minuses
	 ** sizes[3] == pure precision
	 ** sizes[4] == pure width
	 ** sizes[5] == total width
	 ** */
	intmax_t	sizes[6];
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
	if (!(str = malloc(sizeof(char) * (size_t)(sizes[5]) + 1)))
		return (0);
	str[sizes[5]] = '\0';
	tmp = put_stuff(str, sizes, flag, neg);
	if (ft_strsrch("idDuUoOxXpb", flag.conv) != -1)
		printf_int_write(tmp, num, sizes[0], flag);
	else if (ft_strsrch("cC", flag.conv) != -1)
		printf_char_write(&tmp, (unsigned char *)&num.i, flag);
	else //sS
		print_str_write(&tmp, num.p, sizes, flag);
	free(lst->content);
	lst->content = str;
	lst->content_size = (size_t)sizes[5];
	return (1);
}

char	printf_process_conv(t_list *head, t_par *params)
{
	size_t	c;
	t_list	*first;

	first = head;
	c = 0;
	while (head)
	{
		if (!head->content_size)
		{
			if (((t_flag *)head->content)->conv == 'n')
				printf_ptr(&first, head, params, &c);
			else if (ft_strchr("idDuUxXoOsScCpb", ((t_flag *)head->content)->conv))
				printf_flags_hand(head, params, &c);
		}
		head = head->next;
	}
	return (1);
}
