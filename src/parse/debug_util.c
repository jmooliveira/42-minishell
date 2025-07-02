/*debug_utils.c*/

#include "../../include/minishell.h"

static void	print_indent(int depth)
{
	for (int i = 0; i < depth; i++)
		printf("     ");
}

static const char *get_type_name(t_type type)
{
	if (type == WORD || type == WORD_S || type == WORD_D)
		return ("WORD");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == PIPE)
		return ("PIPE");
	if (type == PAR_OPEN)
		return ("PAR_OPEN");
	if (type == PAR_CLOSE)
		return ("PAR_CLOSE");
	if (type == SUBSHELL)
		return ("SUBSHELL");
	if (type == ASSIGNMENT)
		return ("ASSIGNMENT");
	if (type == NONE)
		return ("NONE");
	return ("UNKNOWN");
}

void	print_token(t_token *token_list)
{
	int		i;
	t_token	*current;

	i = 0;
	current = token_list;
	while (current)
	{
		printf("token%d:, type: %s, value: %s\n",
			i, get_type_name(current->type), current->value);
		current = current->next;
		i++;
	}
}

void	print_ast(t_ast *node, int depth)
{
	if (!node)
		return ;
	print_indent(depth);
	printf("• [%s] \"%s\"\n", get_type_name(node->type),
		node->value ? node->value : "NULL");
	if (node->args)
	{
		print_indent(depth + 1);
		printf("args: ");
		for (int i = 0; node->args[i]; i++)
			printf("\"%s\" ", node->args[i]);
		printf("\n");
	}
	if (node->left)
	{
		print_indent(depth);
		printf("├─ left:\n");
		print_ast(node->left, depth + 1);
	}
	if (node->right)
	{
		print_indent(depth);
		printf("└─ right:\n");
		print_ast(node->right, depth + 1);
	}
}
