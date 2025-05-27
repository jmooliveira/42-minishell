NAME		=	minishell
CC			=	cc

# Diretórios
SRC_DIR 	=	src
OBJ_DIR		=	objs
LIB_DIR		=	lib
LIBFT_DIR	=	$(LIB_DIR)
INCLUDES	=	-I $(LIB_DIR)/includes -I ./includes

# Flags
C_FLAGS		=	-Wall -Werror -Wextra $(INCLUDES)

# Libs
LIBFT		=	$(LIB_DIR)/libft.a
LIBS		=	-lreadline -lncurses

# Fontes
SRCS		=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/token.c \
				$(SRC_DIR)/utils_debug.c

OBJS		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Targets
all: $(NAME)

$(NAME): libft $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

libft:
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes --track-fds=yes ./$(NAME)

.PHONY: all clean fclean re libft val
