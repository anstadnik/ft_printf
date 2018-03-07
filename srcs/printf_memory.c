/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:28:59 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/07 17:28:44 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

static void	fill_str(char *str, char *ptr, ssize_t i)
{
	str[--i] = '\0';
	while (--i >= 0)
	{
		if (i % 9 == 8)
		{
			*str++ = ' ';
			ptr++;
		}
		else
			*str++ = ((*ptr >> (i % 9)) & 1) + '0';
	}

}

char				printf_memory(t_list *lst, t_printf_par *params,
		size_t *c)
{
	char			*str;
	t_printf_flags	flag;
	char			*ptr;
	ssize_t			i;

	flag = *(t_printf_flags *)lst->content;
	if (flag.width == -1)
	{
		flag.width = (int)params[flag.wast ? flag.wast - 1 : (*c)++].i;
		if ((int)(flag.width) < 0)
		{
			flag.width = (int)(flag.width) * -1;
			flag.minus = 1;
		}
	}
	free(lst->content);
	i = (ssize_t)(9 * flag.width);
	if (!(str = malloc(sizeof(char) * (size_t)i)))
		return (0);
	ptr = flag.doll ? params[flag.doll - 1].p : params[(*c)++].p;
	fill_str(str, ptr, i);
	lst->content = str;
	lst->content_size = (size_t)(9 * flag.width);
	return (1);
}
