/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:07:19 by jemorais          #+#    #+#             */
/*   Updated: 2025/04/08 20:31:13 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*minishell.h*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "../lib/include/libft.h"

# define NO_PRINTABLE "\t\n\v\f\r "

/* command, |, <, >, >>, <<, undefined */
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	NONE
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char	*prompt;
	int		exit_status;
	t_token	*token_list;
}	t_data;

int		tokenizer_list(t_data *data);
int		get_token(t_data *data, int start);
int		give_id(char *token_def);
t_token	*new_token(char *value, t_token_type type);
void	add_token_to_list(t_data *data, char *token_def, t_token_type id_token);

#endif
