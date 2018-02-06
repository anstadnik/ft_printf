/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_make_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:15:41 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/02 18:45:11 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	err(t_list **head, t_par **params)
{
	if (*head)
		ft_lstdel(head, &free);
	if (*params)
		free(*params);
	return (-1);
}

// Delete
static void f(t_list *elem)
{
	if (elem->content_size)
		ft_putstr(elem->content);
	else
		printf_flags_show(*(t_flag *)elem->content);
}

int			printf_make_str(char **ret, const char *format, va_list arg)
{
	t_list	*head;
	int		params_amount;
	t_par	*params;

	head = NULL;
	ret = NULL;
	if ((params_amount = printf_fill_list(&head, format)) == -1)
		return (0);//(err(&head, &params));
	if ((params = malloc(sizeof(t_par) * (size_t)params_amount)) == NULL)
		return (err(&head, &params));
	printf_get_params(params, head, arg, params_amount);
	/*
	if (printf_process_conv(head, params) == -1)
		return (err(&head, &params));
	if ((*ret = ft_lsttostr(head)) == NULL)
		return (err(&head, &params));
		*/

	/* print params */
	ft_lstiter(head, &f);
	ft_lstdel(&head, &free);
	//free(params);
	return (0);//(int)ft_strlen(*ret));
}
