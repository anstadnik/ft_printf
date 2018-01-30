/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:05:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/30 19:37:23 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_flag	t_flag;
typedef struct s_funcs	t_funcs;
typedef union u_par		t_par;

union					u_par
{
	char				c;/*	1 */
	unsigned char		uc;/*	2 */
	char				*pc;/*	3 */
	short				s;/*	4 */
	unsigned short		us;/*	5 */
	short				*ps;/*	6 */
	long				l;/*	7 */
	unsigned long		ul;/*	8 */
	long				*pl;/*	9 */
	long long			ll;/*	10 */
	unsigned long long	ull;/*	11 */
	long long			*pll;/*	12 */
	intmax_t			imt;/*	13 */
	uintmax_t			uimt;/*	14 */
	intmax_t			*pim;/*	15 */
	size_t				st;/*	16 */
	ssize_t				sst;/*	17 */
	ssize_t				*pst;/*	18 */
	long double			ld;/*	19 */
}

struct					s_funcs
{
	char *	str;
	int		(*f)(t_flag flags, va_list arg, t_list **tail);
};

struct 					s_flag
{
	char	hash;/* # */
	char	zero;/* 0 */
	char	minus;/* - */
	char	plus;/* + */
	char	space;/* space */
	char	apostrophe;/* ' */
	char	modif[7];/* "z", "j", "ll", "l", "hh", "h", "L" */
	char	system;/* base system */
	int		width;/* width (higer priority than wast), negative if dollar*/
	int		prec;/* precision (higer priority than past), negative if dollar*/
	char	wast;/* width asterisk */
	char	past;/* precision asterisk */
	int		doll;/* $ */
	char	conv;/* conversion (sSpdDioOuUxXcCeEfFgGaAnbrk) */
	char	err;/* error (next char) */
};/*  */

int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);
int			ft_asprintf(char **ret, const char *format, ...);

int			printf_make_str(char **ret, const char *format, va_list arg);
t_flag		*printf_parse(const char *str, size_t *i);
int			printf_fill_list(t_list **head, const char *format);
void		printf_get_params(t_par *params, t_list *head, va_list arg);

ssize_t		printf_lsttostr(t_list *head, char **ret);
t_list		*printf_lstnew(void *content, size_t content_size);


int	printf_flags_show(t_flag flags);
#endif
