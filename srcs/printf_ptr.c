/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 09:49:49 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/09 10:54:43 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	count(t_list *head, t_list *lst)
{
	size_t	c;

	c = 0;
	while (head != lst)
	{
		c += head->content_size;
		head = head->next;
	}
	return (c);
}

void			printf_ptr(t_list **head, t_list *lst, t_printf_par *params,
		size_t *c)
{
	unsigned char	*modif;
	void			*p;
	t_printf_flags	*flag;
	size_t			counter;

	counter = count(*head, lst);
	flag = (t_printf_flags *)(lst->content);
	if (!(p = flag->doll ? params[flag->doll - 1].p : params[(*c)++].p))
	{
		ft_lstdelnode(head, lst);
		return ;
	}
	modif = ((t_printf_flags *)(lst->content))->modif;
	modif = ((t_printf_flags *)(lst->content))->modif;
	if (modif[0] || modif[1] || modif[2])
		*(long long *)p = (long long)counter;
	else if (modif[4])
		*(long *)p = (long)counter;
	else if (modif[5])
		*(char *)p = (char)counter;
	else if (modif[6])
		*(short *)p = (short)counter;
	else
		*(int *)p = (int)counter;
	ft_lstdelnode(head, lst);
}
