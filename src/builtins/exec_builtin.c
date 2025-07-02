/*exec_builtin.c*/

#include "../../include/minishell.h"

int	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (EXIT_FAILURE);
	if (!ft_strncmp(cmd->argv[0], "echo", 4))
		return (builtin_echo(cmd->argv));
	if (!ft_strncmp(cmd->argv[0], "cd", 2))
		return (builtin_cd(cmd->argv, data));
	if (!ft_strncmp(cmd->argv[0], "pwd", 3))
		return (builtin_pwd());
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

void	exec_node(t_cmd *cmd, t_data *data)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;

	if (cmd->type == NODE_CMD)
	{
		if (cmd->is_builtin)
			execute_builtin(cmd, data);
		else
		{
			printf("Executável externo ainda não tratado: %s\n", cmd->argv[0]);
			// execute_external(cmd, data);
		}
	}
}

t_cmd	*convert_ast_to_cmd(t_ast *ast, t_gc *gc)
{
	t_cmd	*cmd;

	if (!ast)
		return (NULL);
	cmd = gc_malloc(gc, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	// tipo do nó de execução
	if (ast->type == PIPE)
		cmd->type = NODE_PIPE;
	else if (ast->type == OR || ast->type == AND)
		cmd->type = NODE_LOGIC;
	else if (ast->type == REDIR_IN || ast->type == REDIR_OUT
		|| ast->type == APPEND || ast->type == HEREDOC)
		cmd->type = NODE_REDIR;
	else
		cmd->type = NODE_CMD;
	// argumentos (se for comando simples)
	cmd->argv = ast->args;
	cmd->is_builtin = (cmd->argv && is_builtin(cmd->argv[0]));
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->left = convert_ast_to_cmd(ast->left, gc);
	cmd->right = convert_ast_to_cmd(ast->right, gc);
	return (cmd);
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

// void	exec_ast(t_ast *node, t_data *data)
// {
// 	(void)data; // sera necessário para builtins
// 	if (!node || !node->args || !node->args[0])
// 		return ;
// 	if (!ft_strncmp(node->args[0], "echo", 4))
// 		builtin_echo(node->args);
// 	else
// 		printf("Comando não implementado: %s\n", node->args[0]);
// }
