/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:17:13 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/07 17:37:43 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	g_conv[21] = "sSpdDioOuUxXcCnbkrqm";
static const char	g_flag[8] = "#0-+ \'";
static const char	g_mod[8][3] = {
	"z", "t", "j", "ll", "l", "hh", "h", "L"
};

static int		parse_conv(const char *str, size_t *i, t_printf_flags *flags,
		int *counter)
{
	ssize_t	tmp;

	if ((tmp = ft_strsrch(g_conv, str[*i])) == -1)
		return (0);
	if (!flags->doll)
		(*counter)++;
	else if (flags->doll > (size_t)*counter)
		(*counter) = (int)flags->doll;
	flags->conv = g_conv[tmp];
	if (g_conv[tmp] == 'b')
		flags->system = 2;
	else if (g_conv[tmp] == 'o' || g_conv[tmp] == 'O')
		flags->system = 8;
	else if (g_conv[tmp] == 'x' || g_conv[tmp] == 'X' || g_conv[tmp] == 'p')
		flags->system = 16;
	if (g_conv[tmp] == 'p')
		flags->hash = 1;
	(*i)++;
	if (ft_strchr("SDOUCp", g_conv[tmp]))
		flags->modif[4] = 1;
	return (1);
}

static int		parse_mod_and_fl(const char *str, size_t *i,
		t_printf_flags *flags)
{
	int		j;
	ssize_t	fl;

	j = 0;
	if ((fl = ft_strsrch(g_flag, str[*i])) != -1)
	{
		((char *)flags)[fl] = 1;
		(*i)++;
		return (1);
	}
	else
		while (j < 8)
		{
			if (!ft_strncmp(g_mod[j], str + *i, ft_strlen(g_mod[j])))
			{
				flags->modif[j] = 1;
				*i += ft_strlen(g_mod[j]);
				return (1);
			}
			j++;
		}
	return (0);
}

/*
** Parses flags and returns pointer to flags struct. If an error occured,
** returns NULL
*/

t_printf_flags	*printf_parse(const char *str, size_t *i, int *counter)
{
	t_printf_flags	*flags;

	if (!(flags = ft_memalloc(sizeof(t_printf_flags))))
		return (NULL);
	flags->system = 10;
	flags->width = -2;
	flags->prec = -2;
	while (!parse_conv(str, i, flags, counter) && !flags->err)
		if ((ft_isdigit(str[*i]) && str[*i] != '0') || str[*i] == '*' ||
				str[*i] == '.')
			printf_parse_flag(str, i, flags, counter);
		else if (!parse_mod_and_fl(str, i, flags))
		{
			flags->err = str[*i] ? str[(*i)++] : -1;
			flags->conv = 'c';
			return (flags);
		}
	return (flags);
}
