// test_expand.c

#include "../../include/minishell.h"

int	main(void)
{
	t_gc	*gc;
	char	*result;
	char	*input;
	char	*env[] = {
		"USER=Jefferson",
		"HOME=/home/jeff",
		"SHELL=/bin/bash",
		NULL
	};

	gc = gc_init();
	input = "Olá, $USER!\nHome: $HOME\nShell: $SHELL.";
	result = expand_all_vars(input, env, gc);
	printf("Resultado: %s\n", result);
	gc_clear(gc);
	return (0);
}
