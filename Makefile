NAME		=	minishell
CC			=	cc

# Diretórios
SRC_DIR 	=	src
OBJ_DIR		=	objs
LIB_DIR		=	lib
INPUT_DIR	=	$(SRC_DIR)/input
INIT_DIR	=	$(SRC_DIR)/init
GC_DIR		=	$(SRC_DIR)/garbage
TOKEN_DIR	=	$(SRC_DIR)/token
VALID_DIR	=	$(SRC_DIR)/validate
EXPAND_DIR	=	$(SRC_DIR)/expand
UTILS_DIR	=	$(SRC_DIR)/utils
ERR_DIR		=	$(SRC_DIR)/errors
SIG_DIR		=	$(SRC_DIR)/signal
TEST_DIR	=	$(SRC_DIR)/test
PARSE_DIR	=	$(SRC_DIR)/parse
BUILT_DIR	=	$(SRC_DIR)/builtins
EXEC_DIR	=	$(SRC_DIR)/exec

LIBFT_DIR	=	$(LIB_DIR)
INCLUDES	=	-I $(LIB_DIR)/includes -I ./includes -I $(SRC_DIR)

# Flags
C_FLAGS		=	-Wall -Werror -Wextra -g $(INCLUDES)

# Libs
LIBFT		=	$(LIBFT_DIR)/libft.a
LIBS		=	-lreadline -lncurses

# Fontes principais (minishell)
SRCS		= \
		$(INPUT_DIR)/main.c \
	$(INPUT_DIR)/loop.c \
	$(INIT_DIR)/init.c \
	$(GC_DIR)/garbage_collector.c \
	$(GC_DIR)/gc_utils.c \
	$(TOKEN_DIR)/token.c \
	$(TOKEN_DIR)/token_utils.c \
	$(VALID_DIR)/validate_syntax.c \
	$(VALID_DIR)/validate_utils.c \
	$(EXPAND_DIR)/expand.c \
	$(UTILS_DIR)/utils.c \
	$(ERR_DIR)/handle_errors.c \
	$(SIG_DIR)/signals.c \
	$(SIG_DIR)/signals_handler.c \
	$(PARSE_DIR)/build_ast.c \
	$(PARSE_DIR)/parser.c \
	$(PARSE_DIR)/parser_search.c \
	$(PARSE_DIR)/parser_utils.c \
	$(PARSE_DIR)/debug_util.c \
	$(BUILT_DIR)/exec_builtin.c \
	$(BUILT_DIR)/echo.c \
	$(BUILT_DIR)/cd.c \
	$(BUILT_DIR)/pwd.c \
	$(BUILT_DIR)/env.c \
	$(EXEC_DIR)/exec_ast.c

OBJS		=	$(foreach src,$(SRCS),$(OBJ_DIR)/$(patsubst $(SRC_DIR)/%,%,$(basename $(src))).o)

all: $(NAME)

$(NAME): libft $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@

libft:
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) test_expand
	@make -C $(LIBFT_DIR) fclean

re: fclean all

val:
	@valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes --track-fds=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re libft val test_expand


#ls -l /usr/bin | grep "rwxr-xr-x" | awk '{print $1}' | sort | uniq -c | awk '{print $2}' | sed 's/^[0-9]* //' | sed 's/^[0-9]*//' | sed 's/^ /' | while read line; do echo "Executável: $line"; done