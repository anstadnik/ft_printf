#include "ft_printf.h"

static wchar_t	pull_things(t_flag flag, t_par *params, size_t *c)
{
	if (flag.width < 0)
		flag.width = (wchar_t)params[-flag.width].i;
	else if (flag.wast)
		flag.width = (wchar_t)params[(*c)++].i;
	if (flag.prec < 0)
		flag.prec = (wchar_t)params[-flag.prec].i;
	else if (flag.past)
		flag.prec = (wchar_t)params[(*c)++].i;
	if (flag.doll)
		return ((wchar_t)params[flag.doll].i);
	else
		return ((wchar_t)params[(*c)++].i);
}

static void		get_size(intmax_t *sizes, wchar_t c, t_flag flag)
{
	if (flag.modif[3])
	{
		if (c > 0x1000000 && MB_CUR_MAX >= 4)
			sizes[0] = 4;
		else if (c > 0x10000 && MB_CUR_MAX >= 3)
			sizes[0] = 3;
		else if (c > 0x100 && MB_CUR_MAX >= 2)
			sizes[0] = 2;
		else
			sizes[0] = 1;
	}
	else
		sizes[0] = 1;
	sizes[1] = flag.width - sizes[0];
	if (sizes[1] < 0)
		sizes[1] = 0;
	sizes[2] = sizes[0] + sizes[1] ? sizes[1] : 0;
}

static void	char_conv(char *str, wchar_t c, t_flag flag, intmax_t *sizes)
{
	if (flag.modif[3])
	{
		if (c > 0x1000000 && MB_CUR_MAX >= 4)
			sizes[0] = 4;
		else if (c > 0x10000 && MB_CUR_MAX >= 3)
			sizes[0] = 3;
		else if (c > 0x100 && MB_CUR_MAX >= 2)
			sizes[0] = 2;
		else
			sizes[0] = 1;
	}
	else
		sizes[0] = 1;

}

char		printf_char(t_list *lst, t_par *params, size_t *c) //For c, C
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
	char_conv(flag.minus ? str : str + i - 1, chr, flag);
	return (1);
}
