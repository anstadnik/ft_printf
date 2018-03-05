/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:05:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/05 19:22:53 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include "libft.h"
# include <wchar.h>
# include <limits.h>

typedef struct s_flag	t_flag;
typedef struct s_funcs	t_funcs;
typedef union u_par		t_par;

union					u_par
{
	uintmax_t	i;
	long double		f;
	void			*p;
};

struct 					s_flag
{
	unsigned char		hash;/* # */
	unsigned char		zero;/* 0 */
	unsigned char		minus;/* - */
	unsigned char		plus;/* + */
	unsigned char		space;/* space */
	unsigned char		apostrophe;/* ' */
	unsigned char		modif[8];/* "z", "t", "j", "ll", "l", "hh", "h", "L" */
	unsigned char		system;/* base system */
	intmax_t	width;/* width (if -1 - dollar, see wast, if -2 - not set) */
	intmax_t	prec;/* precision (if -1 - dollar, see past, if -2 - not set) */
	size_t		wast;/* width asterisk, not zero if dollar */
	size_t		past;/* precision asterisk, not zero if dollar */
	size_t		doll;/* $ */
	char		conv;/* conversion (sSpdDioOuUxXcCeEfFgGaAnbrk) */
	char		err;/* error (next char) */
};

int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);
int			ft_asprintf(char **ret, const char *format, ...);
int 		ft_vprintf(const char *format, va_list arg);
int 		ft_vdprintf(int fd, const char *format, va_list arg);

ssize_t		printf_make_str(char **ret, const char *format, va_list arg);
t_flag		*printf_parse(const char *str, size_t *i, int *counter);
int			printf_fill_list(t_list **head, const char *format);
char		printf_process_conv(t_list *head, t_par *params);
void		printf_get_params(t_par *params, t_list *head, va_list arg,
		int params_amount);

ssize_t		printf_lsttostr(t_list *head, char **ret);
t_list		*printf_lstnew(void *content, size_t content_size);

intmax_t	printf_int_size(t_par par, t_flag flag);
char		printf_char_size(wchar_t c, t_flag flag);
void		printf_str_size(intmax_t *sizes, void *c, t_flag flag);
void		printf_int_write(char *str, t_par par, intmax_t len, t_flag flag);
char		printf_char_write(char **str, unsigned char *c, t_flag flag);
void		print_str_write(char **str, void *p, intmax_t *sizes, t_flag flag);
void		printf_ptr(t_list **head, t_list *lst, t_par *params, size_t *c);
char		printf_conv_int(t_list *lst, t_par *par, size_t *c); //For p, d, D, i, o, O, u, U, x, X, b
char		printf_conv_float(t_list *lst, t_par *par, size_t *c); //For e, E, f, F, g, G, a, A
char		printf_conv_string(t_list *lst, t_par *par, size_t *c); //For s, S, maybe r
char		printf_conv_char(t_list *lst, t_par *par, size_t *c); //For c, C
char		printf_conv_pointer(t_list *lst, t_par *par, size_t *c); //For n
char		printf_conv_time(t_list *lst, t_par *par, size_t *c); //For time maybe
int	printf_flags_show(t_flag flags);
#endif
