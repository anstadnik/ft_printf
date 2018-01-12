/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:18:21 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/11 13:30:33 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static intmax_t		pritnf_get_int(t_flags flags, va_list arg)
{
    if (flags.modif[0])
        return (va_arg(arg, intmax_t));
    if (flags.modif[1])
        return (va_arg(arg, intmax_t));
    if (flags.modif[2])
        return (va_arg(arg, long long));
    if (flags.modif[3])
        return (va_arg(arg, long));
    if (flags.modif[4])
        return (va_arg(arg, short));
    if (flags.modif[5])
        return (va_arg(arg, char));
}

static intmax_t		get_size(uintmax_t n, t_flags flags, size_t *size,
		size_t *width)
{
	intmax_t	len;

    len = 1;
	*size = 1;
    while (n =/ len * 10)
	{
		len *= 10;
        (*size)++;
	}
    if (flags.apostrophe)
        *size += (*size - 1) / 3;
    if (flags.hash && flags.system == 16 || flags.system == 8)
        size += flags.system == 16 ? 2 : 1;
	if (((flags.conv == 'd' || flags.conv == 'i') && !flags.system) &&
				(flags.plus || flags.space || (intmax_t)num < 0))
        size++;
    if (size < flags.width || size < flags.prec)
        *width  = flags.width > flags.prec ? flags.width : flags.prec;
	else
		*width  = size;
	return (len);
}

int printf_int(t_flags flags, va_list arg, t_list **tail)
{
    char        *str;
    uintmax_t   num;
    uintmax_t   len;
	size_t		i;
    size_t      size;//amount of the real characters
    size_t      width;//amount of all characters

    num = printf_get_int(flags, arg);
    len = get_size(num, flags, &size, &width);
	if (!str = malloc(sizeof(char) * (width + 1)))
		return (-1);
	i = 0;
	if (width > size && !flags.minus)
		while (width < size)
		{
			str[i++] = ' ';
			width--;
		}
    if (((flags.conv == 'd' || flags.conv == 'i') && !flags.system)
			|| flags.plus || flags.space || (intmax_t)num < 0)
        if ((intmax_t)num < 0)
			str[i++] = ' ';
    if (flags.system == 8 || flags.system == 16) &&)
}
