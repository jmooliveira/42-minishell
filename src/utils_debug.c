/*utils_debug.c*/

#include "../include/minishell.h"

void	print_token(t_token *token_list)
{
	int i = 0;
	t_token	*current = token_list;

	while (current)
	{
		printf("token%d:, id: %d, value: %s\n", i, current->type, current->value);
		current = current->next;
		i++;
	}
}