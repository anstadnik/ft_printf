.PHONY: clean, fclean, re, d#, libft

CC=gcc
CFLAGS= -Wall -Wextra -Werror 
LIBDIR=libft/
ODIR=objs/
SDIR=srcs/
IDIR=includes/
NAME=libftprintf.a
DNAME=printf_debug
FILES=ft_printf.c printf_lst.c printf_make_str.c
OBJS=$(FILES:.c=.o)

all:
	@$(MAKE) $(NAME)

$(NAME): $(addprefix $(ODIR), $(OBJS))
	@$(MAKE) -C $(LIBDIR)
	@echo "\x1b[33mCopying the libft\x1b[0m"
	@cp libft/libft.a $@
	@echo "\x1b[33mAppending to the $(NAME)\x1b[0m"
	@ar -q $@ $(addprefix $(ODIR), $(OBJS))

d: $(DNAME)
	@echo "\x1b[32mRunning your app\x1b[0m"
	@./$(DNAME)

deb: $(DNAME)

$(DNAME): main.c $(SDIR)*.c $(LIBDIR)srcs/*.c
	@echo "\x1b[35mCompiling the $(DNAME)\x1b[0m"
	@$(CC) $(CFLAGS) -I$(IDIR) -I$(LIBDIR)includes -o $@ $^

$(addprefix $(ODIR), %.o): $(addprefix $(SDIR), %.c)
	@echo "\x1b[35mCompiling $@\x1b[0m"
	@$(CC) $(CFLAGS) -I$(IDIR) -I$(LIBDIR)includes -c -o $@ $<

clean:
	@$(MAKE) -C $(LIBDIR) clean
	@echo "\x1b[31mRemoving the object files\x1b[0m"
	@rm -f $(addprefix $(ODIR), $(OBJS))

fclean: clean
	@$(MAKE) -C $(LIBDIR) fclean
	@echo "\x1b[31mRemoving the $(NAME)\x1b[0m"
	@rm -f $(NAME)
	@echo "\x1b[31mRemoving the $(DNAME)"@rm -f $(DNAME)

red:
	@$(MAKE) fclean
	@$(MAKE) d

redeb:
	@$(MAKE) fclean
	@$(MAKE) deb

re: 
	@$(MAKE) fclean
	@$(MAKE) -C $(LIBDIR) re
	@$(MAKE) 
