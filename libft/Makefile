CC=gcc
CFLAGS= -Wall -Wextra -Werror
ODIR=objs/
SDIR=srcs/
IDIR=includes/
NAME=libft.a
FILES=ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_iswhitespace.c ft_itoa.c ft_lstadd.c ft_lstaddb.c ft_lstdel.c ft_lstdelnode.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_lstpushb.c ft_lstpushf.c ft_lsttostr.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memdup.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_realloc.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strsrch.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_pow.c ft_log.c
OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(addprefix $(ODIR), $(OBJS))
	@echo "\n\x1b[33mMaking the libft\x1b[0m"
	@ar rc $@ $^

$(addprefix $(ODIR), %.o): $(addprefix $(SDIR), %.c)
	@printf "."
	@$(CC) $(CFLAGS) -I$(IDIR) -c -o $@ $<

clean:
	@echo "\x1b[31mRemoving the object files\x1b[0m"
	@rm -f $(addprefix $(ODIR), $(OBJS))

fclean: clean
	@echo "\x1b[31mRemoving the $(NAME)\x1b[0m"
	@rm -f $(NAME)

re: 
	@$(MAKE) fclean
	@$(MAKE) 
