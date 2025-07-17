/*main.c*/

#include "../../include/minishell.h"

volatile __sig_atomic_t	g_signal;

void disable_tab_completion(void)
{
    rl_bind_key('\t', rl_insert); // Faz o TAB inserir um tab mesmo, não autocompletar
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Usage: ./minishell\n");
		return (1);
	}
	data = init_data(envp);
	if (!data)
		return (1);
	disable_tab_completion();
	loop(data);
	rl_clear_history();
	gc_clear(data->gc);
	return (0);
}
