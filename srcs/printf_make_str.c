/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_make_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:15:41 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/08 13:29:48 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	g_colors[17][2][15] = {
	{"{black}", "\x1b[30m"}, {"{red}", "\x1b[31m"},
	{"{green}", "\x1b[32m"}, {"{yellow}", "\x1b[33m"},
	{"{blue}", "\x1b[34m"}, {"{magenta}", "\x1b[35m"},
	{"{cyan}", "\x1b[36m"}, {"{white}", "\x1b[37m"},
	{"{eoc}", "\x1b[39m"}, {"{light gray}", "\x1b[90m"},
	{"{light red}", "\x1b[91m"}, {"{light green}", "\x1b[92m"},
	{"{light yellow}", "\x1b[93m"}, {"{light blue}", "\x1b[94m"},
	{"{light magenta}", "\x1b[95m"}, {"{light cyan}", "\x1b[96m"},
	{"{light white}", "\x1b[97m"} };

/*
** Puts the usual string from the format string to the list. Returns -1
** if an error occurs.
*/

static int	printf_add_str(const char *start, size_t length, t_list **tail)
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
	ft_lstaddb(tail, list);
	return (0);
}

/*
** Handles colors. Adds the content to the list, returns the size of color's
** name.
*/

static int	printf_colors(const char *start, t_list **tail)
{
	int		i;

	i = 0;
	while (i < 17)
		if (!ft_strncmp(start, g_colors[i][0], ft_strlen(g_colors[i][0])))
		{
			if (!~printf_add_str(g_colors[i][1],
						ft_strlen(g_colors[i][1]), tail))
				return (-1);
			return ((int)ft_strlen(g_colors[i][0]));
		}
		else
			i++;
	return (1);
}

/*
** Handles the conversions
*/

static int	printf_handler(const char *start, va_list arg, t_list **tail)
{
	t_flag	flags;
	int		i;

	if (*start == '{')
		return (printf_colors(start, tail));
	if (start[1] == '%')
	{
		if (!~printf_add_str("%", 1, tail))
			return (-1);
		return (2);
	}
	i = 1;
	flags = printf_parse_flags(start, arg, &i);
	printf_flags_show(flags, tail);
	//call appropriate function from the function list
	//return
	return (i);
}

/*
** Makes a string based on format and given arguments, puts it to the ret.
** Returns the len of the string.
*/

int			printf_make_str(char **ret, const char *format, va_list arg)
{
	t_list	*head;
	t_list	*tail;
	ssize_t	beg;
	ssize_t	end;

	beg = 0;
	end = -1;
	head = NULL;
	tail = NULL;
	while (beg >= 0 && (!++end || format[end - 1]))
		if ((format[end] == '%') || (format[end] == '{') || !format[end])
		{
			beg = printf_add_str(format + beg, (size_t)(end - beg),
					tail ? &tail : &head);
			if (~beg && format[end])
				beg = printf_handler(format + end, arg, tail ? &tail : &head);
			beg = !~beg ? -1 : beg + end;
			end = beg;
			if (!tail && head)
				tail = head;
		}
	if (beg > 0)
		end = printf_lsttostr(head, ret);
	ft_lstdel(&head, &free);
	return ((int)end);
}
