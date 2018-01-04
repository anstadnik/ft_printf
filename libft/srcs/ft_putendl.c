/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:10:53 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:17:00 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Outputs the string s to the standard output followed by a ’\n’.
*/

#include "libft.h"

void	ft_putendl(char const *s)
{
	if (!s)
		return ;
	ft_putstr(s);
	ft_putchar('\n');
}
