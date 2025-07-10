#include "../../include/minishell.h"
#include <stdio.h>
#include <stdbool.h>

static void print_indent(int depth)
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

void print_token(t_token *token_list)
{
	int i = 0;
	t_token *current = token_list;

	while (current)
	{
		printf("token%d:, type: %s, value: %s\n",
			i, get_type_name(current->type), current->value ? current->value : "(null)");
		current = current->next;
		i++;
	}
}

void print_ast(t_ast *node, int depth)
{
	if (!node)
		return;

	print_indent(depth);
	printf("• [%s] \"%s\"\n", get_type_name(node->type),
		node->value ? node->value : "NULL");

	if (node->args)
	{
		print_indent(depth + 1);
		printf("args: ");
		for (int i = 0; node->args[i]; i++)
			printf("\"%s\" ", node->args[i] ? node->args[i] : "(null)");
		printf("\n");
	}

	if (node->redir)
	{
		print_indent(depth + 1);
		printf("redirs:\n");
		t_redir *redir = node->redir;
		while (redir)
		{
			// Verifica se o ponteiro é válido e o tipo está no intervalo do enum esperado
			if (!redir)
				break;

			bool valid_type = (redir->type >= WORD && redir->type <= NONE);
			print_indent(depth + 2);
			printf("- [%s]", valid_type ? get_type_name(redir->type) : "INVALID_TYPE");

			if (redir->type == HEREDOC)
			{
				// delim e filename podem ser NULL, trate aqui para não imprimir NULL como string
				printf(" delim: \"%s\", tmp: \"%s\"",
					redir->delim ? redir->delim : "(null)",
					redir->filename ? redir->filename : "(null)");
			}
			else
			{
				printf(" filename: \"%s\"", redir->filename ? redir->filename : "(null)");
			}
			printf("\n");

			redir = redir->next;
		}
	}

	if (node->left)
	{
		print_indent(depth);
		printf("├─ left:\n");
		// print_ast(node->left, depth + 1);
	}

	if (node->right)
	{
		print_indent(depth);
		printf("└─ right:\n");
		// print_ast(node->right, depth + 1);
	}
}
