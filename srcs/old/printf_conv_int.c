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

static size_t		i;
static size_t		len;//int of the type of 10^n, which the number can be divided
static size_t		size;//amount of the real characters
static size_t		width;//amount of all characters
static uintmax_t	num;

static uintmax_t	printf_get_uint(t_flag flags, va_list arg)
{
    if (flags.modif[0] || flags.conv == 'p')
        return (va_arg(arg, uintmax_t));
    if (flags.modif[1])
        return (va_arg(arg, uintmax_t));
    if (flags.modif[2])
        return (va_arg(arg, unsigned long long));
    if (flags.modif[3] || flags.conv == 'D' || flags.conv == 'O' ||
			flags.conv == 'U')
        return (va_arg(arg, unsigned long));
    if (flags.modif[4])
        return ((unsigned short)va_arg(arg, int));
    return ((unsigned char)va_arg(arg, int));
}

static void		get_size(uintmax_t n, t_flag flags)
{
	//TODO: change minus size error
	len = 1;
	size = 1;
    while (n / (len * (size_t)flags.system))
	{
		len *= (size_t)flags.system;
        (size)++;
	}
    if (flags.apostrophe)
        size += (size - 1) / 3;
    if (flags.hash && (flags.system == 16 || flags.system == 8))
        size += flags.system == 16 ? 2 : 1;
	if (((flags.conv == 'd' || flags.conv == 'i') && !flags.system) &&
				(flags.plus || flags.space || (intmax_t)num < 0))
        size++;
    if (size < (size_t)flags.width || size < (size_t)flags.prec)
        width = flags.width > flags.prec ? (size_t)flags.width : (size_t)flags.prec;
	else
		width = size;
}

static void		printf_atoi_base(char *str, t_flag flags)
{
	char	base[] = "0123456789abcdef";
	
	if (width > size && flags.zero)
		while (width-- > size)
			str[i++] = '0';
	if (flags.prec > (int)size)
		while (flags.prec-- > (int)size)
			str[i++] = '0';
	while (num)
	{
		str[i++] = base[(size_t)(num / len)];
		if (flags.apostrophe && len > (size_t)(3 * flags.system) && !(len % (size_t)(3 * flags.system)) && MB_CUR_MAX > 0)
				str[i++] = ',';//change this
		num %= len;
		len /= flags.system ? (size_t)flags.system : 10;
	}
}

int 			printf_conv_int(t_flag flags, va_list arg, t_list **tail)
{
    char        *str;
	t_list		*list;

    num = printf_get_uint(flags, arg);
    get_size(num, flags);
	i = 0;
	if (!(str = malloc(sizeof(char) * (width + 1))))
		return (-1);
	str[width] = '\0';
	if (flags.width > (int)size && !flags.minus && !flags.zero)
		while (flags.width-- > (int)size)
			str[i++] = ' ';
    if ((!flags.system && (intmax_t)num < 0) || flags.plus || flags.space)
	{
        if (!flags.system && (intmax_t)num < 0)
		{
			str[i++] = '-';
			num = (uintmax_t)((intmax_t)num * -1);
		}
		else
			str[i++] = flags.space ? ' ' : '+';
	}
    if ((flags.conv == 'x' || flags.conv == 'X') && flags.hash)
		ft_strcpy(str + i, flags.conv == 'x' ? "0x" : "0X");
    if ((flags.conv == 'o' || flags.conv == 'O') && flags.hash)
		str[i++] = '0';
	printf_atoi_base(str, flags);
	if (flags.width > (int)size && flags.minus && !flags.zero)
		while (flags.width-- > (int)size)
			str[i++] = ' ';
	if (!(list = printf_lstnew(str, i)))
	{
		free(str);
		return (-1);
	}
	ft_lstaddb(tail, list);
	return (0);
}
