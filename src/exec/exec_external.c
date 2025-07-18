/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:41:19 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:54:47 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_and_check_cmd_path(t_ast *node, t_data *data, t_gc *gc)
{
	char	*cmd_path;

	if (ft_strchr(node->args[0], '/'))
	{
		cmd_path = gc_strdup(node->args[0], gc);
		if (access(cmd_path, F_OK) != 0)
		{
			print_error_not_found(data, node, "No such file or directory");
			return (NULL);
		}
	}
	else
	{
		cmd_path = find_executable(node->args[0], data->env, gc);
		if (!cmd_path || access(cmd_path, F_OK) != 0)
		{
			print_error_not_found(data, node, "command not found");
			return (NULL);
		}
	}
	return (cmd_path);
}

static void	handle_child_process(char *cmd_path, t_ast *node, t_data *data)
{
	setup_signals(0);
	execve(cmd_path, node->args, data->env);
	perror("minishell");
	exit(126);
}

static void	handle_parent_process(pid_t pid, t_data *data)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			printf("Quit (core dumped)\n");
		data->exit_status = 128 + WTERMSIG(status);
	}
	else
		data->exit_status = 1;
}

int	execute_external(t_ast *node, t_data *data, t_gc *gc)
{
	pid_t		pid;
	struct stat	sb;
	char		*cmd_path;

	if (!node || !node->args || !node->args[0])
		return (1);
	cmd_path = get_and_check_cmd_path(node, data, gc);
	if (!cmd_path)
		return (data->exit_status);
	if (stat(cmd_path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (print_error(data, cmd_path, "Is a directory"));
	if (access(cmd_path, X_OK) != 0)
		return (print_error(data, cmd_path, NULL));
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		data->exit_status = 1;
	}
	else if (pid == 0)
		handle_child_process(cmd_path, node, data);
	else
		handle_parent_process(pid, data);
	return (data->exit_status);
}
