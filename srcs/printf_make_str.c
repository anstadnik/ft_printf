/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_make_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:15:41 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/27 17:56:23 by astadnik         ###   ########.fr       */
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

int			printf_make_str(char **ret, const char *format, va_list arg)
{
	t_list	*head;
	int		params_amount;
	t_par	*params;

	head = NULL;
	if (!~(params_amount = printf_fill_list(&head, format)))
		return (err(&head, &params));
	if (!(params = malloc(sizeof(t_par) * params_amount)))
		return (err(&head, &params));
	printf_get_params(params, head, arg);
	if (!~printf_process_conv(head, params))
		return (err(&head, &params));
	*ret = ft_lsttostr(head);
	ft_lstdel(&head, &free);
	free(params);
	if (*ret)
		return (ft_strlen(*ret));
	return (-1);
}
