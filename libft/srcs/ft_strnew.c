/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:03:34 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:22 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a “fresh” string ending
** with ’\0’. Each character of the string is initialized at
** ’\0’. If the allocation fails the function returns NULL.
*/

#include "libft.h"

char	*ft_strnew(size_t size)
{
	return ((char *)ft_memalloc(size + 1));
}
