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
	// basico
	WORD,
	WORD_S,
	WORD_D,
	// redirecionamento
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	// operadores logicos
	AND,
	OR,
	PIPE,
	// parenteses e subshell
	PAR_OPEN,
	PAR_CLOSE,
	SUBSHELL,
	// variaveis ambiente e outros
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
	bool				expandable;
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
	char			**args;
	struct s_ast	*right;
	struct s_ast	*left;
}	t_ast;

typedef struct s_data
{
	const char	*prompt;		//str indicativa ex: "minishell$ "
	char		*input;			//linha de comando (read_line())
	char		**env;			//array de var de ambiente
	int			env_len;		//comprimento desse arr
	int			exit_status;	//saida padrao do ultimo comando executado
	int			fd_bk[2];		//bk dos fds
	t_gc		*gc;
	t_env		*envl;
	t_token		*token_list;	
	t_ast		*tree;
}	t_data;

// adiciondao para o ast, parser e builtins
typedef enum e_node_type
{
	NODE_CMD,     // comando simples: echo, ls, etc.
	NODE_PIPE,    // pipe: |
	NODE_REDIR,   // redirecionamento: >, <, >>, <<
	NODE_LOGIC    // operadores lógicos: &&, ||
}	t_node_type;

typedef struct s_cmd
{
	t_node_type	type;
	char		**argv;	// comando e argumentos: ["echo", "oi"]
	bool		is_builtin;	// true se for builtin
	int			infile;	// fd de entrada, se houver
	int			outfile;	 // fd de saída, se houver
	struct s_cmd	*left;	// para operadores como pipe ou &&
	struct s_cmd	*right;
}	t_cmd;


// FUNCTIONS:

//MAIN

// INIT
t_data	*init_data(char **ev);
char	**copy_env(char **ev, t_gc *gc);
int		count_envlen(char **ev);

// LOOP
void	loop(t_data *data);

size_t	ft_strspn(const char *s, const char *accept);

// TOKEN:
int		tokenizer_list(t_data *data);
int		get_token(t_data *data, int start);
int		find_token_end(char *inpt, int start);
int		give_id(char *token_def);
void	add_token_to_list(t_data *data, char *token_def, t_type id_token);

// TOKEN_UTILS
t_token	*new_token(char *value, t_type type, t_gc *gc);
void	delete_token_list(t_token **token_l, t_gc *gc);
char	*trim_quotes(char *str, t_gc *gc);
int		skip_quotes(char *input, int start);
t_token	*ft_token_last(t_token *lst);

// EXPAND
void	expand_token_values(t_data *data);
char	*expand_all_vars(const char *str, char **env, t_gc *gc);
// static char	*normal_char(const char *str, int *i, t_gc *gc, char *result);
// static char	*get_var_expansion(const char *str, int *i, char **env, t_gc *gc);
char	*get_env_value(const char *var_name, char **env);

// VALIDATE_SINTAX
int		validate_syntax(t_data *data);
int		check_first_node(t_token *token_l);
int		check_last_node(t_token *token_l);
int		check_invalid_op(t_token *token_l);
int		check_unbalanced_parentheses(t_token *token_list);

int		check_empty_parentheses(t_token *token_l);
int		check_invalid_redir(t_token *token_l);
int		is_word(t_type type);
int		is_redir(t_type type);
int		is_logical_op(t_type type);

int		syntax_error(char *msg, t_data *data);

// PARSE
t_token 	*find_operator(t_token *tokens);
t_token		*find_redir(t_token *tokens);
t_ast		*parse_subshell(t_token *tokens, t_gc *gc);
t_ast   	*parse_operator(t_token *tokens, t_token *op, t_gc *gc);
t_ast   	*parse_cmd(t_token *tokens, t_gc *gc);
t_ast   	*parse_redir(t_token *tokens, t_token *op, t_gc *gc);
bool    	is_operator(t_type type);
bool    	is_redir_bool(t_type type);
int			is_subshell(t_token *tokens);
t_token 	*create_token_copy(t_token *src, t_gc *gc);
t_token		*slice_tokens(t_token *start, t_token *end, t_gc *gc);
void		handle_error(char *msg, t_data *data);
t_ast   	*create_node_ast(char *value, t_type type, t_gc *gc);
int			get_args_len(t_token *tokens);
char		**extract_args(t_token *tokens, t_gc *gc);
t_ast   	*build_ast(t_token *tokens, t_gc *gc);
void    	parse(t_data *data);
void		print_ast(t_ast *node, int depth);

// GARBAGE COLLECTOR
t_gc	*gc_init(void);
void	*gc_malloc(t_gc *gc, size_t size);
void	*gc_calloc(size_t nmemb, size_t size, t_gc *gc);
void	gc_add(t_gc *gc, void *ptr);

char	*gc_strjoin(char *s1, char *s2, t_gc *gc);
char	*gc_substr(char const *s, unsigned int start, size_t len, t_gc *gc);
char	*gc_strdup(const char *s, t_gc *gc);
void	gc_free(t_gc *gc, void *ptr);
void	gc_clear(t_gc *gc);

// DEBUG UTILS
void	print_token(t_token *token_list);

// EXEC BUILTINS
bool	is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_data *data);
void	exec_ast(t_ast *node, t_data *data);

int		builtin_echo(char **argv);

// UTILS LIST

#endif
