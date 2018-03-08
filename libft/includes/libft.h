/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:35:10 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/05 14:18:03 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_log(unsigned long long n);
unsigned long long	ft_pow(unsigned long long n, int p);
void				*ft_realloc(void *ptr, size_t size_src, size_t size);
void				ft_lstaddb(t_list **head, t_list *list);
void				ft_lstadd(t_list **alst, t_list *elem);
void				ft_lstpushb(t_list **list, void *content,
		size_t content_size);
void				ft_lstdel(t_list **alst, void (*del)(void *));
void				ft_lstdelone(t_list **aslt, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstgetlast(t_list *head);
void				ft_lstpushf(t_list **alst, void *content,
		size_t content_size);
void				ft_lstdelnode(t_list **head, t_list *targ);
char				*ft_lsttostr(t_list *head);
void				ft_putchar(char c);
void				ft_putstr(char const *str);
void				ft_putendl(char const *str);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *str, int fd);
void				ft_putendl_fd(char const *str, int fd);
void				ft_putnbr_fd(int n, int fd);
void				*ft_memdup(void *src, size_t size);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
void				*ft_memccpy(void *s1, void const *s2, int c, size_t n);
void				*ft_memset(void *str, int c, size_t n);
void				*ft_memcpy(void *str1, const void *str2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_memmove(void *s1, const void *s2, size_t n);
ssize_t				ft_strsrch(const char *str, char c);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strcat(char *s1, char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(char const *s1, char const *s2);
char				*ft_strcpy(char *s1, char const *s2);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *s1, char *s2, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *s1, char *s2, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_iswhitespace(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_atoi(const char *s);
char				*ft_itoa(int n);
void				ft_bzero(void *s, size_t n);

#endif
