/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flags_show.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 11:32:50 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/30 17:51:17 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	g_mod[7][3] = {"z", "j", "ll", "l", "hh", "h", "L"};

int	printf_flags_show(t_flag flags)
{
	char	*str;
	char	*tmp;

	str = malloc(120);
	ft_strcpy(str, "\x1b[31m");
	ft_strcat(str, "{#: ");
	ft_strcat(str, flags.hash ? "1" : "0");
	ft_strcat(str, ", 0: ");
	ft_strcat(str, flags.zero ? "1" : "0");
	ft_strcat(str, ", -: ");
	ft_strcat(str, flags.minus ? "1" : "0");
	ft_strcat(str, ", +: ");
	ft_strcat(str, flags.plus ? "1" : "0");
	ft_strcat(str, ",  : ");
	ft_strcat(str, flags.space ? "1" : "0");
	ft_strcat(str, ", ': ");
	ft_strcat(str, flags.apostrophe ? "1" : "0");
	ft_strcat(str, ", !: ");
	tmp = ft_itoa(flags.system);
	ft_strcat(str, tmp);
	free(tmp);
	ft_strcat(str, ", modif: ");
	for (int i = 0; i < 7; i++)
		if (flags.modif[i] != 0)
		{
			ft_strcat(str, (char *)g_mod[i]);
			ft_strcat(str, ", ");
		}
	ft_strcat(str, ", width: ");
	tmp = ft_itoa(flags.width);
	ft_strcat(str, tmp);
	free(tmp);
	ft_strcat(str, ", prec: ");
	tmp = ft_itoa(flags.prec);
	ft_strcat(str, tmp);
	free(tmp);
	ft_strcat(str, ", err : ");
	if (flags.err)
	{
		str[ft_strlen(str) + 1] = '\0';
		str[ft_strlen(str)] = flags.err;
	}
	ft_strcat(str, ", conv: ");
	str[ft_strlen(str) + 1] = '\0';
	str[ft_strlen(str)] = flags.conv;
	ft_strcat(str, "}\x1b[39m");
	ft_putstr(str);
	free(str);
	/* list = printf_lstnew(str, 0); */
	/* ft_lstaddb(tail, list); */
	return ((int)ft_strlen(str));
}
