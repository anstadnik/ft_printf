/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:32:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/02 18:30:56 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	g_conv[] = "sSpdDioOuUxXcCeEfFgGaAnbrk";
static const char	g_flag[] = "#0-+ '";
static const char	g_mod[7][3] = {"z", "j", "ll", "l", "hh", "h", "L"};

static int		parse_conv(const char *str, size_t *i, t_flag *flags)
{
	char	*tmp;

	tmp = ft_strchr(g_conv, str[*i]);
	if (!tmp)
		return (0);
	flags->conv = *tmp;
	if (flags->conv == 'o' || flags->conv == 'O')
		flags->system = 8;
	if (flags->conv == 'x' || flags->conv == 'X')
		flags->system = 16;
	(*i)++;
	return (1);
}

static int		parse_mod_and_fl(const char *str, size_t *i, t_flag *flags)
{
	int		j;
	size_t	fl;

	j = 0;
	if ((fl = ft_strsrch(g_flag, str[*i])))
	{
		((char *)flags)[fl] = 1;
		(*i)++;
		return (1);
	}
	else
		while (j < 7)
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

static void		parse_num(const char *str, size_t *i, t_flag *flags)
{
	int	tmp;

	if (ft_isdigit(str[*i]))
	{
		tmp = ft_atoi(str + *i);
		while (ft_isdigit(str[*i]))
			(*i)++;
		if (str[*i] == '!' && (*i)++)
			flags->system = tmp > 16 ? 10 : (char)tmp;
		else if (str[*i] == '$' && (*i)++)
			flags->doll = (size_t)tmp;
		else
			flags->width = tmp;
	}
	else if (str[*i] == '.')
	{
		(*i)++;
		if (ft_isdigit(str[++(*i)]))
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
					flags->prec = -tmp;
					(*i)++;
				}
				else
				{
					flags->width = tmp;
					flags->prec = 0;
					flags->past = 0;
				}
			}
			else
			{
				flags->prec = 0;
				flags->past = 1;
			}
		}
		else
		{
			flags->prec = 0;
			flags->past = 0;
		}
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
				flags->width = -tmp;
				(*i)++;
			}
			else
				flags->err = str[(*i)++];
		}
		else
		{
			flags->width = 0;
			flags->wast = 1;
		}
	}
}

/*
 ** Parses flags and returns pointer to flags struct. If an error occured,
 ** returns NULL
 */

t_flag	*printf_parse(const char *str, size_t *i)
{
	t_flag	*flags;

	if (!(flags = ft_memalloc(sizeof(t_flag))))
		return (NULL);
	flags->system = 10;
	while (!parse_conv(str, i, flags) && !flags->err)
	{
		if (!str[*i])
		{
			free(flags);
			return (NULL);
		}
		else if (ft_isdigit(str[*i]) || str[*i] == '*' || str[*i] == '.')
			parse_num(str, i, flags);
		else if (!parse_mod_and_fl(str, i, flags))
		{
			flags->err = str[(*i)++];
			return (flags);
		}
	}
	return (flags);
}
