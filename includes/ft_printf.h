/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:05:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/02/02 18:29:53 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include "libft.h"
# include <wchar.h>

typedef struct s_flag	t_flag;
typedef struct s_funcs	t_funcs;
typedef union u_par		t_par;

union					u_par
{
	uintmax_t	i;
	//double			d;
	long double		f;
	void			*p;
	/* char				c; */
	/* unsigned char		uc; */
	/* char				*pc; */
	/* short				s; */
	/* unsigned short		us; */
	/* short				*ps; */
	/* int					i; */
	/* long				l; */
	/* unsigned long		ul; */
	/* long				*pl; */
	/* long long			ll; */
	/* unsigned long long	ull; */
	/* long long			*pll; */
	/* intmax_t			imt; */
	/* uintmax_t			uimt; */
	/* intmax_t			*pim; */
	/* size_t				st; */
	/* ssize_t				sst; */
	/* ssize_t				*pst; */
	/* wint_t				wi; */
	/* wchar_t				wc; */
	/* double				d; */
	/* long double			ld; */
};

struct					s_funcs
{
	char *	str;
	int		(*f)(t_flag flags, va_list arg, t_list **tail);
};

struct 					s_flag
{
	char		hash;/* # */
	char		zero;/* 0 */
	char		minus;/* - */
	char		plus;/* + */
	char		space;/* space */
	char		apostrophe;/* ' */
	char		modif[7];/* "z", "j", "ll", "l", "hh", "h", "L" */
	char		system;/* base system */
	intmax_t	width;/* width (higer priority than wast), negative if dollar*/
	intmax_t	prec;/* precision (higer priority than past), negative if dollar*/
	char		wast;/* width asterisk */
	char		past;/* precision asterisk */
	size_t		doll;/* $ */
	char		conv;/* conversion (sSpdDioOuUxXcCeEfFgGaAnbrk) */
	char		err;/* error (next char) */
};

int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);
int			ft_asprintf(char **ret, const char *format, ...);

int			printf_make_str(char **ret, const char *format, va_list arg);
t_flag		*printf_parse(const char *str, size_t *i);
int			printf_fill_list(t_list **head, const char *format);
char		printf_process_conv(t_list *head, t_par *params);
void		printf_get_params(t_par *params, t_list *head, va_list arg,
		int params_amount);

ssize_t		printf_lsttostr(t_list *head, char **ret);
t_list		*printf_lstnew(void *content, size_t content_size);

char		printf_int(t_list *lst, t_par *params, size_t *c); //For p, d, D, i, o, O, u, U, x, X, b
char		printf_float(t_list *lst, long double n); //For e, E, f, F, g, G, a, A
char		printf_string(t_list *lst, void *p); //For s, S, maybe r
char		printf_char(t_list *lst, t_par *params, size_t *c); //For c, C
char		pritnf_pointer(t_list *lst, t_par *par); //For n
char		printf_time(t_list *lst, t_par *par); //For time maybe
int	printf_flags_show(t_flag flags);
#endif
