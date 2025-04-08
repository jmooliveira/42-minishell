/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:07:19 by jemorais          #+#    #+#             */
/*   Updated: 2025/04/08 18:37:28 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*minishell.h*/

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdbool.h>
#include "../lib/include/libft.h"

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
} t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char	*prompt;
	t_token	*token_list;
}	t_data;

bool	tokenizer_list(char *input, t_data *data);

#endif
