NAME		=	minishell

CC			=	cc

HEADERS		=	-I $(LIBFT)/includes -I ./includes

FLAGS		=	-Wall -Werror -Wextra ${HEADERS}

LIBFT		=	lib

LIB			=	$(LIBFT)/libft.a

SRCS		=	./src/main.c \
				./src/token.c

OBJS		=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
OBJ_DIR		=	objs
VPATH		=	./src

all: libft ${NAME}

libft:
	@make -C $(LIBFT)

${NAME}: ${OBJS}
	@$(CC) $(OBJS) $(LIB) $(HEADERS) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(OBJ_DIR)
	${CC} ${FLAGS} -o $@ -c $<

clean:
	@rm -rf ${OBJS}
	@$(MAKE) -C $(LIBFT) clean

fclean:	clean
	@rm -rf ${NAME}
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes --track-fds=yes ./minishell

.PHONY: all clean fclean re libft
