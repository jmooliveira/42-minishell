/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:59:57 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:59:58 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*generate_heredoc_tmp(t_gc *gc)
{
	static int	id = 0;
	char		*tmp;
	char		*id_str;
	char		*pid_str;
	char		*suffix;

	id_str = gc_itoa(id++, gc);
	pid_str = gc_itoa(getpid(), gc);
	suffix = gc_strjoin(pid_str, "_", gc);
	suffix = gc_strjoin(suffix, id_str, gc);
	tmp = gc_strjoin("/tmp/.hd_tmp_", suffix, gc);
	return (tmp);
}

static void	print_eof_warning(char *delim)
{
	ft_putstr_fd("minishell: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putendl_fd("')", 2);
}

static int	handle_line(int fd, char *line, char *delim)
{
	if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		return (1);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (0);
}

static int	read_and_write_heredoc(int fd, char *delim)
{
	char	*line;

	while (42)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal == SIGINT)
				return (130);
			print_eof_warning(delim);
			break ;
		}
		if (handle_line(fd, line, delim))
			break ;
		free(line);
	}
	free(line);
	return (0);
}

int	exec_heredoc(char *filename, char *delim)
{
	int		fd;
	int		status;

	g_signal = 0;
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (print_redir_error(filename, NULL));
	heredoc_signal();
	status = read_and_write_heredoc(fd, delim);
	close(fd);
	interactive_signal();
	return (status);
}
