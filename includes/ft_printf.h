/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:05:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/01/27 18:00:11 by astadnik         ###   ########.fr       */
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
	char				c;
	unsigned char		uc;
	char				*pc;
	short				s;
	unsigned short		us;
	short				*ps;
	long				l;
	unsigned long		ul;
	long				*pl;
	long long			ll;
	unsigned long long	ull;
	long long			*pll;
	intmax_t			imt;
	uintmax_t			uimt;
	intmax_t			*pim;
	size_t				st;
	ssize_t				sst;
	ssize_t				*pst;
	long double			ld;
}

struct					s_funcs
{
	char *	str;
	int		(*f)(t_flag flags, va_list arg, t_list **tail);
};

struct 					s_flag
{
	char	hash;
	char	zero;
	char	minus;
	char	plus;
	char	space;
	char	apostrophe;
	char	modif[7];
	char	system;
	int		width;
	int		prec;
	char	conv;
	char	err;
};

int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);
int			ft_asprintf(char **ret, const char *format, ...);

int			printf_make_str(char **ret, const char *format, va_list arg);
int			printf_fill_list(t_list **head, char *format);

#endif
