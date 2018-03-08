/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_make_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:15:41 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/08 19:46:09 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Frees all allocated memory.
*/

static ssize_t	err_free(t_list **head, t_printf_par **params)
{
	if (*head)
		ft_lstdel(head, &free);
	if (*params)
		free(*params);
	return (-1);
}

/*
** Makes the string and puts it int the ret. Return it's len, or -1 if an
** error has occured.
*/

ssize_t			printf_make_str(char **ret, const char *format, va_list arg)
{
	t_list			*head;
	int				params_amount;
	t_printf_par	*params;
	ssize_t			rez;

	head = NULL;
	*ret = NULL;
	params = NULL;
	/* ft_putendl_fd("1", 2); */
	if ((params_amount = printf_fill_list(&head, format)) == -1)
		return (err_free(&head, &params));
	/* ft_putendl_fd("2", 2); */
	if (params_amount)
	{
		if (!(params = malloc(sizeof(t_printf_par) * (size_t)params_amount)))
			return (err_free(&head, &params));
		else
			printf_get_printf_params(params, head, arg, params_amount);
	}
	/* ft_putendl_fd("3", 2); */
	if (printf_process_conv(head, params) == -1)
		return (err_free(&head, &params));
	/* ft_putendl_fd("4", 2); */
	if ((rez = (int)printf_lsttostr(head, ret)) == -1)
		return (err_free(&head, &params));
	/* ft_putendl_fd("5", 2); */
	ft_lstdel(&head, &free);
	free(params);
	/* ft_putendl_fd("6", 2); */
	return (rez);
}
