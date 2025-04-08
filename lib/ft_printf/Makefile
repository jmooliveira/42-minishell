# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 12:10:56 by jemorais          #+#    #+#              #
#    Updated: 2025/02/10 14:24:33 by jemorais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_printf.a

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra

SRCS		=	ft_printf.c ft_printf_utils1.c ft_printf_utils2.c get_next_line_bonus.c

HEADER		=	ft_printf.h get_next_line_bonus.h

AR			=	ar rcs

RM			=	rm -rf

OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(AR) $(NAME) $(OBJS)

%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

 .PHONY: all clean fclean re
