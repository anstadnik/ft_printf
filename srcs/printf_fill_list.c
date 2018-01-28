/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fill_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:57:07 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/28 20:39:35 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	g_counter;

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
** Adds string to the list.
** If ptr is empty: just malloc, elsewise pushb and change ptr to
** it's last elem
*/

static void	printf_add_str(const char *start, size_t length, t_list **list)
{
	char	*str;
	t_list	*node;

	if (!length)
		return ;
	if (!(str = ft_strsub(start, 0, length)) ||
			!(node = printf_lstnew(str, length)))
	{
		free(str);
		g_counter = -1;
		return ;
	}
	ft_lstaddb(list, node);
}

/*
** Handles colors. Adds the content to the list, returns the size of color's
** name.
*/

static void	printf_colors(const char *start, t_list **list, size_t *end)
{
	int		i;

	i = 0;
	while (i < 17)
		if (!ft_strncmp(start, g_colors[i][0], ft_strlen(g_colors[i][0])))
		{
			printf_add_str(g_colors[i][1], ft_strlen(g_colors[i][1]), list);
			*end += ft_strlen(g_colors[i][0]);
			return ;
		}
		else
			i++;
}

/*
** Handles the conversions
*/

static void	printf_handler(const char *str, size_t *end, t_list **list)
{
	t_flag	*flags;
	t_list	*node;
	char	f;

	if (str[*end] == '{')
		printf_colors(str, list, end);
	else if (str[*end + 1] == '%')
	{
		printf_add_str("%", 1, list);
		*end += 2;
	}
	else
	{
		if (!(flags = printf_parse_flags(str, end)) ||
				!(node = printf_lstnew(flags, 0)))
		{
			free(flags);
			g_counter = -1;
			return ;
		}
		f = *list ? 1 : 0;
		ft_lstaddb(list, node);
		if (f)
			*list = node;
		g_counter++;
	}
}

/*
** Fills list with strings and structs, if it was a conversion. Returns -1
** if an error has occured.
*/

int	printf_fill_list(t_list **head, const char *format)
{
	t_list	*tail;
	size_t	beg;
	size_t	end;

	beg = 0;
	end = 0;
	g_counter = 0;
	tail = NULL;
	while (g_counter != -1 && format[end])
	{
		while ((format[end] != '%') && (format[end] != '{') && format[end])
			end++;
		printf_add_str(format + beg, end - beg, tail ? &tail : head);
		if (format[end] && g_counter != -1)
			printf_handler(format, &end, tail ? &tail : head);
		beg = end;
		if (!tail && *head)
			tail = *head;
	}
	ft_lstdel(head, &free);
	return (g_counter);
}
