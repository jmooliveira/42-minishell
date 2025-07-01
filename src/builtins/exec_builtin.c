/*exec_builtin.c*/

#include "../../include/minishell.h"

int	execute_builtin(t_cmd *cmd, t_data *data)
{
	(void)data; // sera necessário para builtin
	if (!ft_strncmp(cmd->argv[0], "echo", 4))
		return (builtin_echo(cmd->argv));
	// if (!ft_strncmp(cmd->argv[0], "cd", 2))
	// 	return (builtin_cd(cmd->argv, data));
	// if (!ft_strncmp(cmd->argv[0], "pwd", 3))
	// 	return (builtin_pwd());
	// if (!ft_strncmp(cmd->argv[0], "export", 6))
	// 	return (builtin_export(cmd->argv, &data->env));
	// if (!ft_strncmp(cmd->argv[0], "unset", 5))
	// 	return (builtin_unset(cmd->argv, &data->env));
	// if (!ft_strncmp(cmd->argv[0], "env", 3))
	// 	return (builtin_env(data->env));
	// if (!ft_strncmp(cmd->argv[0], "exit", 4))
	// 	return (builtin_exit(cmd->argv, data));
	return (EXIT_FAILURE);
}

bool	is_builtin(char *cmd_name)
{
	return (!ft_strncmp(cmd_name, "echo", 4)
		|| !ft_strncmp(cmd_name, "cd", 4)
		|| !ft_strncmp(cmd_name, "pwd", 4)
		|| !ft_strncmp(cmd_name, "export", 4)
		|| !ft_strncmp(cmd_name, "unset", 4)
		|| !ft_strncmp(cmd_name, "env", 4)
		|| !ft_strncmp(cmd_name, "exit", 4));
}

// void	exec_ast(t_ast *node, t_data *data)
// {
// 	if (!node)
// 		return ;
// 	if (node->type == WORD && node->args && node->args[0])
// 	{
// 		if (is_builtin(node->args[0]))
// 			execute_builtin(node->args, data);
// 		// else
// 		// 	execute_external(node, data); // chama fork + execve
// 	}
// 	// else if (node->type == NODE_PIPE)
// 	// 	exec_pipe(node, data); // a ser implementado no bônus
// 	// else if (node->type == NODE_REDIR)
// 	// 	exec_redirection(node, data); // opcional, dependendo do seu parser
// }

void	exec_ast(t_ast *node, t_data *data)
{
	(void)data; // sera necessário para builtins
	if (!node || !node->args || !node->args[0])
		return ;
	if (!ft_strncmp(node->args[0], "echo", 4))
		builtin_echo(node->args);
	else
		printf("Comando não implementado: %s\n", node->args[0]);
}
