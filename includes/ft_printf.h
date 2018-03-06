/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:05:42 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/06 17:49:16 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include "libft.h"
# include <wchar.h>
# include <limits.h>

typedef struct s_printf_flags	t_printf_flags;
typedef struct s_printf_funcs	t_printf_funcs;
typedef union u_printf_par		t_printf_par;

union					u_printf_par
{
	uintmax_t		i;
	void			*p;
};

struct					s_printf_funcs
{
	char			*s;
	intmax_t		(*printf_size)(t_printf_par par, t_printf_flags flag);
	void			(*printf_write)(char *str, t_printf_par par, intmax_t len, t_printf_flags flag);
};

struct 					s_printf_flags
{
	unsigned char	hash;/* # */
	unsigned char	zero;/* 0 */
	unsigned char	minus;/* - */
	unsigned char	plus;/* + */
	unsigned char	space;/* space */
	unsigned char	apostrophe;/* ' */
	unsigned char	modif[8];/* "z", "t", "j", "ll", "l", "hh", "h", "L" */
	unsigned char	system;/* base system */
	intmax_t		width;/* width (if -1 - dollar, see wast, if -2 - not set) */
	intmax_t		prec;/* precision (if -1 - dollar, see past, if -2 - not set) */
	size_t			wast;/* width asterisk, not zero if dollar */
	size_t			past;/* precision asterisk, not zero if dollar */
	size_t			doll;/* $ */
	char			conv;/* conversion (sSpdDioOuUxXcCeEfFgGaAnbrk) */
	char			err;/* error (next char) */
};

int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);
int			ft_asprintf(char **ret, const char *format, ...);
int 		ft_vprintf(const char *format, va_list arg);
int 		ft_vdprintf(int fd, const char *format, va_list arg);

ssize_t		printf_make_str(char **ret, const char *format, va_list arg);
t_printf_flags		*printf_parse(const char *str, size_t *i, int *counter);
void		printf_parse_flag(const char *str, size_t *i, t_printf_flags *flags, int *counter);
int			printf_fill_list(t_list **head, const char *format);
char		printf_process_conv(t_list *head, t_printf_par *params);
void		printf_get_printf_params(t_printf_par *params, t_list *head, va_list arg,
		int params_amount);
char		printf_flags_hand(t_list *lst, t_printf_par *params, size_t *c);

ssize_t		printf_lsttostr(t_list *head, char **ret);
t_list		*printf_lstnew(void *content, size_t content_size);

intmax_t	printf_char_size(t_printf_par par, t_printf_flags flag);
intmax_t	printf_str_size(t_printf_par par, t_printf_flags flag);
void	printf_char_write(char *str, t_printf_par par, intmax_t len, t_printf_flags flag);
void	printf_str_write(char *str, t_printf_par par, intmax_t len, t_printf_flags flag);

intmax_t	printf_int_size(t_printf_par par, t_printf_flags flag);
void		printf_int_write(char *str, t_printf_par par, intmax_t len, t_printf_flags flag);
void		printf_ptr(t_list **head, t_list *lst, t_printf_par *params, size_t *c);
char		printf_conv_int(t_list *lst, t_printf_par *par, size_t *c); //For p, d, D, i, o, O, u, U, x, X, b
char		printf_conv_float(t_list *lst, t_printf_par *par, size_t *c); //For e, E, f, F, g, G, a, A
char		printf_conv_string(t_list *lst, t_printf_par *par, size_t *c); //For s, S, maybe r
char		printf_conv_char(t_list *lst, t_printf_par *par, size_t *c); //For c, C
char		printf_conv_pointer(t_list *lst, t_printf_par *par, size_t *c); //For n
char		printf_conv_time(t_list *lst, t_printf_par *par, size_t *c); //For time maybe
int	printf_flags_show(t_printf_flags flags);
#endif
