/*exec_ast.c*/

#include "../../include/minishell.h"

int	exec_cmd(t_ast *node, t_data *data)
{
	if (!node || !node->args || !node->args[0] || node->args[0][0] == '\0')
	{
		data->exit_status = 0;
		return (0);
	}
	if (is_builtin(node->args[0]))
		return (execute_builtin(node, data));
	else
		return (execute_external(node, data, data->gc));
}

int	exec_ast(t_ast *node, t_data *data)
{
	if (!node)
		return (1);
	if (node->type == PIPE)
		return (execute_pipe(node, data));
	if (node->type == AND || node->type == OR)
		return (execute_and_or(node, data));
	if (node->type == SUBSHELL)
		return (execute_subshell(node, data));
	if (is_redir(node->type))
		return (execute_redir(node, data));
	if (is_word(node->type) && node->redir)
		return (execute_redir(node, data));
	if (node->type == WORD && node->args && node->args[0])
		return (exec_cmd(node, data));
	return (data->exit_status);
}
