/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_make_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:15:41 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/04 18:01:53 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Makes a string based on format and given arguments, puts it to the ret.
** Returns the len of the string.
*/

#include "ft_printf.h"

static int	printf_add_str(const char *start, int length, t_list **head)
{
	char	*str;
	t_list	*list;

	if (!(str = ft_strsub(start, 0, length)))
		return (-1);
	if (!(list = printf_lstnew(str, 0)))
	{
		free(str);
		return (-1);
	}
	ft_lstaddb(head, list);
	return (length);
}

int			printf_make_str(char **ret, const char *format, va_list arg,
		va_list arg_start)
{
	t_list	*head;
	int		tmp;
	int		beg;
	int		end;

	va_copy(arg, arg_start);//gotta delete it
	beg = 0;
	end = 0;
	head = NULL;
	while (end >= 0)
	{
		/*
		if ((format[end] == '%') || (format[end] == '{'))
			//potato
		else */
		if (!format[end])
		{
			tmp = printf_add_str(format + beg, end - beg, &head);
			end = tmp == -1 ? -1 : end;
			break ;
		}
		else
			end++;
	}
	if (end >= 0)
		*ret = printf_lsttostr(head);
	ft_lstdel(&head, &free);
	return (end >= 0 && *ret ? end : -1);
}
