/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:05:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/06 11:00:57 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

typedef struct s_flag	t_flag;

struct s_flag
{
	unsigned char	hash : 1;
	unsigned char	zero : 1;
	unsigned char	minus : 1;
	unsigned char	plus : 1;
	unsigned char	space : 1;
	unsigned char	apostrophe : 1;
	int				dollar;
	char[2]			modif;
	int				width;
	int				prec;
	char			conv;
}

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_asprintf(char **ret, const char *format, ...);

int		printf_make_str(char **ret, const char *format, va_list arg,
		va_list arg_beg);
t_list	*printf_lstnew(void *content, size_t content_size);
char	*printf_lsttostr(t_list	*head, size_t size);
#endif
