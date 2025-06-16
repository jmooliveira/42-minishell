// test_expand.c

#include "../../include/minishell.h"

int	main(void)
{
	t_gc	*gc;
	char	*result;
	char	*env[] = {
		"USER=Roberto",
		"HOME=/home/jeff",
		"SHELL=/bin/bash",
		NULL
	};

	gc = gc_init();

	char *input = "Olá, $USER! VSF e obrigado, $HOME e shell é $SHELL.";
	result = expand_all_vars(input, env, gc);
	printf("Resultado: %s\n", result);

	gc_clear(gc);
	return (0);
}
