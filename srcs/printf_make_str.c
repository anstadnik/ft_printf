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


/*
** Frees all allocated memory.
*/

static int	err(t_list **head, t_par **params)
{
	if (*head)
		ft_lstdel(head, &free);
	if (*params)
		free(*params);
	return (-1);
}

/*
** Temporary printf function
*/

/* static void f(t_list *elem) */
/* { */
/* 	if (elem->content_size) */
/* 		ft_putstr(elem->content); */
/* 	else */
/* 		printf_flags_show(*(t_flag *)elem->content); */
/* } */

/*
** Makes the string and puts it int the ret. Return it's len, or -1 if an
** error has occured.
*/

int	printf_make_str(char **ret, const char *format, va_list arg)
{
	t_list	*head;
	int	params_amount;
	t_par	*params;
	int		rez;

	head = NULL;
	*ret = NULL;

	/* Fill list with strings or parameters */ 
	if ((params_amount = printf_fill_list(&head, format)) == -1)
		return (0);//(err(&head, &params));

	/* Allocate array of parameters */ 
	if ((params = malloc(sizeof(t_par) * (size_t)params_amount)) == NULL)
		return (err(&head, &params));

	/* Get params from va_list */ 
	printf_get_params(params, head, arg, params_amount);

	/* Convers params to strings */
	if (printf_process_conv(head, params) == -1)
		return (err(&head, &params));

	/* Convert list with strings to string */
	/* Change this (ft_lsttostr has different signature now) */
	if ((rez = (int)printf_lsttostr(head, ret)) == 0)
		return (err(&head, &params));

	/* print params */
	//ft_lstiter(head, &f);
	ft_lstdel(&head, &free);
	//free(params);
	return (rez);//(int)ft_strlen(*ret));
}
