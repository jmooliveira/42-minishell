/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:35:18 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:35:19 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_builtin(t_ast *node, t_data *data)
{
	int	status;

	status = 0;
	if (!node || !node->args || !node->args[0])
		return (EXIT_FAILURE);
	if (!ft_strncmp(node->args[0], "echo", 4))
		status = (builtin_echo(node->args));
	if (!ft_strncmp(node->args[0], "cd", 2))
		status = (builtin_cd(node->args, data));
	if (!ft_strncmp(node->args[0], "pwd", 3))
		status = (builtin_pwd());
	if (!ft_strncmp(node->args[0], "export", 6))
		status = (builtin_export(node->args, data));
	if (!ft_strncmp(node->args[0], "unset", 5))
		status = (builtin_unset(node->args, data));
	if (!ft_strncmp(node->args[0], "env", 3))
		status = (builtin_env(data->env));
	if (!ft_strncmp(node->args[0], "exit", 4))
		status = (builtin_exit(node->args, data));
	data->exit_status = status;
	return (data->exit_status);
}

bool	is_builtin(const char *node)
{
	return (!ft_strncmp(node, "echo", 4) || !ft_strncmp(node, "cd", 2)
		|| !ft_strncmp(node, "pwd", 3) || !ft_strncmp(node, "export", 6)
		|| !ft_strncmp(node, "unset", 5) || !ft_strncmp(node, "env", 3)
		|| !ft_strncmp(node, "exit", 4));
}
