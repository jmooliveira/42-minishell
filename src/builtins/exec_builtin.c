/*exec_builtin.c*/

#include "../../include/minishell.h"

int	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (builtin_echo(cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (builtin_cd(cmd->argv, data));
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (builtin_export(cmd->argv, &data->env));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (builtin_unset(cmd->argv, &data->env));
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (builtin_env(data->env));
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (builtin_exit(cmd->argv, data));
	return (EXIT_FAILURE);
}
