/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:32:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/01 13:25:15 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	g_conv[] = "sSpdDioOuUxXcCeEfFgGaAnbrk";
static const char	g_flag[] = "#0-+ '";
static const char	g_mod[8][3] = {"z", "t", "j", "ll", "l", "hh", "h", "L"};

static int		parse_conv(const char *str, size_t *i, t_flag *flags, int *counter)
{
	ssize_t	tmp;

	tmp = ft_strsrch(g_conv, str[*i]);
	if (tmp == -1)
		return (0);

	if (flags->doll)
	{
		if (flags->doll > (size_t)*counter)
			(*counter) = (int)flags->doll;
	}
	else
		(*counter)++;
	flags->conv = g_conv[tmp];
	if (g_conv[tmp] == 'o' || g_conv[tmp] == 'O')
		flags->system = 8;
	if (g_conv[tmp] == 'x' || g_conv[tmp] == 'X' || g_conv[tmp] == 'p')
		flags->system = 16;
	if (g_conv[tmp] == 'p')
	{
		flags->hash = 1;
		flags->modif[4] = 1;
	}
	(*i)++;
	if (ft_strchr("SDOUCFGA", g_conv[tmp]))
		flags->modif[4] = 1;
	return (1);
}

static int		parse_mod_and_fl(const char *str, size_t *i, t_flag *flags)
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
** I gotta change this. I should try to make it smaller and also try to
** do the same but in the stupider way. It means that I shouldn't cycle
** through the flags but just go one by one, and if there is a mistake in the
** positioning, I should count it as an error.
*/

static void		parse_num(const char *str, size_t *i, t_flag *flags, int *counter)
{
	int	tmp;

	if (ft_isdigit(str[*i]))
	{
		tmp = ft_atoi(str + *i);
		while (ft_isdigit(str[*i]))
			(*i)++;
		if (str[*i] == '!' && (*i)++)
			flags->system = tmp > 16 ? 10 : (unsigned char)tmp;
		else if (str[*i] == '$' && (*i)++)
			flags->doll = (size_t)tmp;
		else
			flags->width = tmp;
	}
	else if (str[*i] == '.')
	{
		(*i)++;
		if (ft_isdigit(str[*i]))
		{
			tmp = ft_atoi(str + *i);
			while (ft_isdigit(str[*i]))
				(*i)++;
			flags->prec = tmp;
		}
		else if (str[*i] == '*')
		{
			(*i)++;
			if (ft_isdigit(str[*i]))
			{
				tmp = ft_atoi(str + *i);
				while (ft_isdigit(str[*i]))
					(*i)++;
				if (str[*i] == '$')
				{
					flags->prec = -1;
					flags->past = (size_t)tmp;
					(*i)++;
					if (tmp > *counter)
						(*counter) = tmp;
				}
				else
					flags->width = tmp;
			}
			else
			{
				flags->prec = -1;
				flags->past = 0;
				(*counter)++;
			}
		}
		else
			flags->prec = 0;
	}
	else if (str[*i] == '*')
	{
		(*i)++;
		if (ft_isdigit(str[*i]))
		{
			tmp = ft_atoi(str + *i);
			while (ft_isdigit(str[*i]))
				(*i)++;
			if (str[*i] == '$')
			{
				flags->width = -1;
				flags->wast = (size_t)tmp;
				(*i)++;
				if (tmp > *counter)
					(*counter) = tmp;
			}
			else
				flags->width = str[(*i)++];
		}
		else
		{
			flags->width = -1;
			flags->wast = 0;
			(*counter)++;
		}
	}
}

/*
** Parses flags and returns pointer to flags struct. If an error occured,
** returns NULL
*/

t_flag	*printf_parse(const char *str, size_t *i, int *counter)
{
	t_flag	*flags;

	if (!(flags = ft_memalloc(sizeof(t_flag))))
		return (NULL);
	flags->system = 10;
	flags->width = -2;
	flags->prec = -2;
	while (!parse_conv(str, i, flags, counter) && !flags->err)
	{
		if (parse_mod_and_fl(str, i, flags))
			continue;
		else if (ft_isdigit(str[*i]) || str[*i] == '*' || str[*i] == '.')
			parse_num(str, i, flags, counter);
		else
		{
			flags->err = str[*i];
			flags->conv = 'c';
			if (str[*i])
				(*i)++;
			return (flags);
		}
	}
	return (flags);
}
