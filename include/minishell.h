
/*minishell.h*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/include/libft.h"

# define NO_PRINTABLE " \t\n\v\f\r "

typedef enum e_type
{
	// comandos e argumentos
	ARG,
	WORD_S,
	WORD_D,
	PIPE,
	AND,
	OR,
	PAR_OPEN,
	PAR_CLOSE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	SUBSHELL,
	ASSIGNMENT,
	NONE
}	t_type;

// GARBAGE COLLECTOR STRUCTS
typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node			*head;
}	t_gc;

// MINISHELL STRUCTS
typedef struct s_token
{
	t_type				type;
	char				*value;
	struct s_token		*next;
	// struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;		
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_ast
{
	t_type			type;
	char			*value;
	struct s_ast	*right;
	struct s_ast	*left;
}	t_ast;

typedef struct s_data
{
	const char	*prompt;		//str indicativa para digitar comando ex: "minishell$ "
	char		*input;			//linha de comando (read_line())
	char		**env;			//array de var de ambiente
	int			env_len;		//comprimento desse arr
	int			exit_status;	//saida padrao do ultimo comando executado
	int			fd_bk[2];		//bk dos fds
	t_gc		*gc;
	t_env		*envl;
	t_token		*token_list;	
	t_ast		**tree;
}	t_data;

// FUNCTIONS:

//MAIN:

// INIT:
t_data	*init_data(char **ev);
void	loop(t_data *data);

// UTILS LIST
t_token	*ft_token_last(t_token *lst);

//TOKEN:
int			tokenizer_list(t_data *data);
int			get_token(t_data *data, int start);
int			give_id(char *token_def);
void		add_token_to_list(t_data *data, char *token_def, t_type id_token);
void		delete_token_list(t_token **token_l, t_gc *gc);
t_token		*new_token(char *value, t_type type, t_gc *gc);

// SYNTAXE VALIDATE
int		syntax_error(char *msg, t_data *data);
int		validate_syntax(t_data *data);

// GARBAGE COLLECTOR
void	*gc_malloc(t_gc *gc, size_t size);
void	gc_add(t_gc *gc, void *ptr);
void	gc_clear(t_gc *gc);
void	gc_free(t_gc *gc, void *ptr);
void	*gc_calloc(size_t nmemb, size_t size, t_gc *gc);
char	*gc_strdup(const char *s, t_gc *gc);
char	*gc_substr(char const *s, unsigned int start, size_t len, t_gc *gc);
t_gc	*gc_init(void);

// DEBUG UTILS
void	print_token(t_token *token_list);

#endif
