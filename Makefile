.PHONY: clean, fclean, re#, libft

CC=gcc
CFLAGS= -Wall -Wextra -Werror 
LIBDIR=libft/
ODIR=objs/
SDIR=srcs/
IDIR=includes/
NAME=libftprintf.a
FILES=
OBJS=$(FILES:.c=.o)

all:
	$(MAKE) $(NAME)

$(NAME): $(addprefix $(ODIR), $(OBJS))
	$(MAKE) -C $(LIBDIR)
	cp libft/libft.a $@
	ar -q $@ $(addprefix $(ODIR), $(OBJS))

debug: main.c $(SDIR)*.c $(LIBDIR)srcs/*.c
	$(CC) $(CFLAGS) -I$(IDIR) -I$(LIBDIR)includes -o printf_debug @^

$(addprefix $(ODIR), %.o): $(addprefix $(SDIR), %.c)
	$(CC) $(CFLAGS) -I$(IDIR) -c -o $@ $<

clean:
	$(MAKE) -C $(LIBDIR) clean
	rm -f $(addprefix $(ODIR), $(OBJS))

fclean: clean
	$(MAKE) -C $(LIBDIR) fclean
	rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) -C $(LIBDIR) re
	$(MAKE) 
