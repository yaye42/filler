# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaye <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 11:17:35 by yaye              #+#    #+#              #
#    Updated: 2019/11/28 11:17:37 by yaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = yaye.filler
FLGS = -Wall -Wextra -Werror
LBFT = libft/libft.a
LB_H = libft/includes/libft.h
LB_S = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c \
ft_strnstr.c ft_strrchr.c ft_strstr.c ft_tolower.c ft_toupper.c ft_strlen.c \
ft_strdup.c ft_strncpy.c ft_strncat.c ft_strlcat.c ft_strncmp.c ft_memalloc.c \
ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c \
ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstaddbel.c ft_power.c \
ft_lstiter.c ft_lstmap.c ft_lstlst.c ft_lstlast.c ft_strsplit_lst.c \
ft_abs.c ft_hexatod.c ft_atoi_base.c ft_printbits.c get_next_line.c \
ft_printf.c parse.c parse_di.c parse_o.c parse_u.c parse_x.c parse_xcap.c \
parse_c.c parse_s.c parse_p.c parse_f.c parse_b.c
HEAD = includes/filler.h
SRCS = filler.c solver.c tools.c

all : $(NAME)

$(NAME) : $(LBFT) $(HEAD) $(addprefix sources/, $(SRCS))
	@gcc $(FLGS) -o $(NAME) $(LBFT) $(addprefix sources/, $(SRCS)) \
	-I includes -I libft/includes
	@echo "\033[32m  yaye.filler CREATED\033[0m"

$(LBFT) : $(LB_H) $(addprefix libft/sources/, $(LB_S))
	@make -C libft

clean :
	@make clean -C libft

fclean :
	@rm -f $(NAME)
	@echo "\033[31m  yaye.filler REMOVED\033[0m"
	@make fclean -C libft

re : fclean $(NAME)
