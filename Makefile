.PHONY: clean, fclean, re, d#, libft

CC=gcc
CFLAGS= -Wall -Wextra -Werror -Wconversion
LIBDIR=libft/
LIB=$(LIBDIR)libft.a
ODIR=objs/
SDIR=srcs/
IDIR=includes/
NAME=libftprintf.a
DNAME=printf_debug
FILES= ft_printf.c printf_fill_list.c printf_flags_show.c printf_funcs.c printf_get_params.c printf_make_str.c printf_parse.c
OBJS=$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(addprefix $(ODIR), $(OBJS))
	@echo "\x1b[33mCopying the libft\x1b[0m"
	@cp libft/libft.a $@
	@echo "\x1b[33mAppending to the $(NAME)\x1b[0m"
	@ar -q $@ $(addprefix $(ODIR), $(OBJS))

$(LIB):
	@$(MAKE) -C $(LIBDIR)

d: $(DNAME)
	@echo "\x1b[32mRunning your app\x1b[0m"
	@./$(DNAME) "{red}R{yellow}A{light yellow}I{green}N{cyan}B{blue}O{magenta}W{eoc}"

deb: $(DNAME)

$(DNAME): main.c $(LIBDIR)/srcs/*.c $(addprefix $(SDIR), $(FILES))
	@echo "\x1b[35mCompiling the $(DNAME)\x1b[0m"
	@$(CC) $(CFLAGS) -g -I$(IDIR) -I$(LIBDIR)includes -o $@ $^

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
	@echo "\x1b[31mRemoving the $(DNAME)"
	@rm -f $(DNAME)
	@rm -rf printf_debug.dSYM

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
