/*exec_builtin.c*/

#include "../../include/minishell.h"

int	execute_builtin(t_ast *node, t_data *data)
{
	if (!node || !node->args || !node->args[0])
		return (EXIT_FAILURE);
	if (!ft_strncmp(node->args[0], "echo", 4))
		return (builtin_echo(node->args));
	if (!ft_strncmp(node->args[0], "cd", 2))
		return (builtin_cd(node->args, data));
	if (!ft_strncmp(node->args[0], "pwd", 3))
		return (builtin_pwd());
	// if (!ft_strncmp(node->args[0], "export", 6))
	// 	return (builtin_export(node->args, &data->env));
	// if (!ft_strncmp(node->args[0], "unset", 5))
	// 	return (builtin_unset(node->args, &data->env));
	if (!ft_strncmp(node->args[0], "env", 3))
		return (builtin_env(data->env));
	// if (!ft_strncmp(node->args[0], "exit", 4))
	// 	return (builtin_exit(node->args, data));
	return (EXIT_FAILURE);
}

bool	is_builtin(const char *node)
{
	return (!ft_strncmp(node, "echo", 4) || !ft_strncmp(node, "cd", 2)
		|| !ft_strncmp(node, "pwd", 3) || !ft_strncmp(node, "export", 6)
		|| !ft_strncmp(node, "unset", 5) || !ft_strncmp(node, "env", 3)
		|| !ft_strncmp(node, "exit", 4));
}
