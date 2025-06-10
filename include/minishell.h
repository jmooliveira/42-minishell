/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:07:19 by jemorais          #+#    #+#             */
/*   Updated: 2025/06/10 15:31:59 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*minishell.h*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "../lib/include/libft.h"

# define NO_PRINTABLE " \t\n\v\f\r "

/* command, |, <, >, >>, <<, &&, ||, |, (, ), (), Variavel */
typedef enum e_type
{
	// comandos e argumentos
	ARG,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	// operadores lógicos
	AND,
	OR,
	PIPE,
	// parenteses e subshell
	PARENT_OPEN,
	PARENT_CLOSE,
	SUBSHELL,
	ASSIGNMENT,
	NONE
}	t_type;


typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
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



//MAIN:


#endif
