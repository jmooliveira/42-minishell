/*exec_ast.c*/

#include "../../include/minishell.h"

// TEM LEAK PARA RESOLVER

void	exec_ast(t_ast *node, t_data *data)
{
	if (!node)
		return ;
	if (node->type == WORD && node->args && node->args[0])
	{
		if (is_builtin(node->args[0]))
		{
			data->exit_status = execute_builtin(node, data);
			// Executa a builtin
			// execute_builtin(node, data);
		}
	// 	else
	// 	{
	// 		// Executa comandos externos (fork + execve)
	// 		printf("Executável externo ainda não tratado: %s\n", node->args[0]);
	// 		// execute_external(node, data); // Implementar esta função
	// 	}
	// }
	// else if (node->type == PIPE)
	// {
	// 	// Implementar lógica para pipes
	// 	printf("Pipe ainda não tratado\n");
	// }
	// else if (is_redir(node->type))
	// {
	// 	// Implementar lógica para redirecionamentos
	// 	printf("Redirecionamento ainda não tratado\n");
	// }
	// else if (node->type == SUBSHELL)
	// {
	// 	// Executa subshell
	// 	exec_ast(node->left, data);
	// }
	// else
	// {
	// 	// Percorre os filhos da árvore
	// 	exec_ast(node->left, data);
	// 	exec_ast(node->right, data);
	}
}

// void	execute_external(t_ast *node, t_data *data)
// {
// 	pid_t pid;
// 	int status;

// 	if (!node || !node->args || !node->args[0])
// 		return ;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		// Processo filho
// 		execve(node->args[0], node->args, data->env);
// 		perror("minishell");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid > 0)
// 	{
// 		// Processo pai
// 		waitpid(pid, &status, 0);
// 		data->exit_status = WEXITSTATUS(status);
// 	}
// 	else
// 	{
// 		perror("fork");
// 	}
// }
