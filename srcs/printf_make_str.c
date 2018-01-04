/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_make_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:15:41 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/04 20:41:55 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Handles colors. Adds the content to the list, returns the size of color's
** name.
*/

static int	printf_colors(const char *start, t_list **head)
{
	char	 colors[7][2][9] = {
				{"{red}", "\x1b[31m"},
				{"{green}", "\x1b[32m"},
				{"{yellow}", "\x1b[33m"},
				{"{blue}", "\x1b[34m"},
				{"{magenta}", "\x1b[35m"},
				{"{cyan}", "\x1b[36m"},
				{"{reset}", "\x1b[0m"} };
	int		i;
	char	*str;
	t_list	*list;

	i = 0;
	while (i < 7)
		if (!ft_strncmp(start, colors[i][0], ft_strlen(colors[i][0])))
		{
			if (!(str = ft_strdup(colors[i][1])))
				return (-1);
			if (!(list = printf_lstnew(str, 0)))
			{
				free(str);
				return (-1);
			}
			ft_lstaddb(head, list);
			return (ft_strlen(colors[i][0]));
		}
		else
			i++;
	return (0);
}

/*
** Handles the conversions
*/

static int	printf_handler(const char *start, va_list arg, va_list arg_beg,
		t_list **head)
{
	va_copy(arg, arg_beg);//gonna change this
	if (*start == '{')
		return (printf_colors(start, head));
	return (0);
}

/*
** Puts the usual string from the format string to the list. Returns -1
** if an error occurs.
*/

static int	printf_add_str(const char *start, int length, t_list **head)
{
	char	*str;
	t_list	*list;

	if (!length)
		return (0);
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

/*
** Makes a string based on format and given arguments, puts it to the ret.
** Returns the len of the string.
*/

int			printf_make_str(char **ret, const char *format, va_list arg,
		va_list arg_beg)
{
	t_list	*head;
	int		rez;
	int		beg;
	int		end;

	beg = 0;
	end = 0;
	head = NULL;
	while (beg >= 0 && (!end || format[end - 1]))
	{
		if ((format[end] == '%') || (format[end] == '{') || !format[end])
		{
			rez = 0;
			if (printf_add_str(format + beg, end - beg, &head) == -1)
				break ;
			if (format[end])
				rez = printf_handler(format + end, arg, arg_beg, &head);
			beg = rez == -1 ? -1 : end + rez;
			end = beg;
		}
		end++;
	}
	if (beg >= 0)
		*ret = printf_lsttostr(head);
	ft_lstdel(&head, &free);
	return (beg >= 0 && *ret ? (int)ft_strlen(*ret): -1);
}
