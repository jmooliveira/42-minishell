/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:41:37 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:51:09 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cleanup_heredoc_files(t_redir *r)
{
	while (r)
	{
		if (r->type == HEREDOC && r->filename)
			unlink(r->filename);
		r = r->next;
	}
}

void	restore_fds(t_data *data)
{
	dup2(data->fd_bk[0], STDIN_FILENO);
	dup2(data->fd_bk[1], STDOUT_FILENO);
	close(data->fd_bk[0]);
	close(data->fd_bk[1]);
}
