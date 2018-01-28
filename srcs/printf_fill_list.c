/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fill_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:57:07 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/27 20:27:18 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	g_counter;

/*
** Fills list with strings and structs, if it was a conversion. Returns -1
** if an error has occured.
*/

int	printf_fill_list(t_list **head, char *format)
{
	t_list	*tail;
	char	err;
	size_t	beg;
	size_t	end;

	err = 0;
	beg = 0;
	end = 0;
	g_counter = 0;
	tail = NULL;
	while (!err && format[end])
	{
		while ((format[end] != '%') && (format[end] != '{') && format[end])
			end++;
		//if ptr is empty: just malloc, elsewise pushb and change ptr to
		//it's last elem
		err = printf_add_str(format + beg, end - beg, tail ? &tail : head);
		if (!format[end])
			break ;
		if (!err)
			err = printf_handler(format + end, tail ? &tail : head);
		beg += end;
		end = beg;
		if (!tail && *head)
			tail = *head;
	}
	ft_lstdel(head, &free);
	return (err ? -1 : g_counter);
}
