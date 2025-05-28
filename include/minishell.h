/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:07:19 by jemorais          #+#    #+#             */
/*   Updated: 2025/05/28 18:43:35 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ARG,
	PIPE,
	AND,
	OR,
	PARENT_OPEN,
	PARENT_CLOSE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	ASSIGNMENT,					//para criar variaveis de ambiente
	SUBSHELL,					//para utilizar o parenteses
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
	t_env		*envl;
	t_token		*token_list;	
	t_ast		**tree;
}	t_data;


// FUNCTIONS:

//TOKEN:
int			tokenizer_list(t_data *data);
int			get_token(t_data *data, int start);
int			give_id(char *token_def);
void		add_token_to_list(t_data *data, char *token_def, t_type id_token);
t_token		*new_token(char *value, t_type type);

// DEBUG UTILS
void	print_token(t_token *token_list);

// GARBAGE COLLECTOR
void	*gc_malloc(t_gc *gc, size_t size);
void	gc_add(t_gc *gc, void *ptr);
void	gc_clear(t_gc *gc);
t_gc	*gc_init(void);

//MAIN:


#endif
