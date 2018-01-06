/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:05:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/06 18:50:03 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

typedef struct s_flag	t_flag;

struct 					s_flag
{
	char	hash;
	char	zero;
	char	minus;
	char	plus;
	char	space;
	char	apostrophe;
	int		dollar;
	char	modif[7];
	char	system;
	int		width;
	int		prec;
	char	conv;
};

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_asprintf(char **ret, const char *format, ...);

int		printf_make_str(char **ret, const char *format, va_list arg);
t_list	*printf_lstnew(void *content, size_t content_size);
char	*printf_lsttostr(t_list	*head, size_t size);
#endif
