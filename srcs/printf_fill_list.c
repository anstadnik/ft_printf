/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fill_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:57:07 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/16 14:05:07 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		g_counter;
static t_list	*g_tail;
size_t			g_end;

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

static void	printf_add_str(const char *start, size_t length, t_list **head)
{
	char	*str;
	t_list	*node;

	if (!length)
		return ;
	str = NULL;
	if (!(str = ft_strsub(start, 0, length)) ||
			!(node = printf_lstnew(str, length)))
	{
		if (str)
			free(str);
		g_counter = -1;
		return ;
	}
	ft_lstaddb(*head ? &g_tail : head, node);
	g_tail = node;
}

/*
** Handles colors. Adds the content to the list, returns the size of color's
** name.
*/

static void	printf_colors(const char *start, t_list **head)
{
	int		i;

	i = 0;
	while (i < 17)
		if (!ft_strncmp(start + g_end, g_colors[i][0], ft_strlen(g_colors[i][0])))
		{
			printf_add_str(g_colors[i][1], ft_strlen(g_colors[i][1]), head);
			g_end += ft_strlen(g_colors[i][0]);
			return ;
		}
		else
			i++;
	printf_add_str("{", 1, head);
	(g_end)++;
}

/*
** Handles the conversions
*/

static void	printf_handler(const char *str, t_list **head)
{
	t_flag	*flags;
	t_list	*node;

	if (str[g_end] == '{')
		printf_colors(str, head);
	else
	{
		(g_end)++;
		if (!(flags = printf_parse(str, &g_end, &g_counter)) ||
				!(node = printf_lstnew(flags, 0)))// Try arraylist
		{
			if (flags)
				free(flags);
			g_counter = -1;
			return ;
		}
		ft_lstaddb(*head ? &g_tail : head, node);
		g_tail = node;
	}
}

/*
** Fills list with strings and structs, if it was a conversion. Returns -1
** if an error has occured.
*/

int		printf_fill_list(t_list **head, const char *format)
{
	size_t	beg;

	beg = 0;
	g_end = 0;
	g_counter = 0;
	g_tail = NULL;
	while (g_counter != -1 && format[g_end])
	{
		while (format[g_end] != '%' && format[g_end] != '{' && format[g_end])
			g_end++;
		printf_add_str(format + beg, g_end - beg, head);
		if (format[g_end] && g_counter != -1)
			printf_handler(format, head);
		beg = g_end;
	}
	return (g_counter);
}
