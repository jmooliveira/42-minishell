/*main.c*/

#include "../../include/minishell.h"

volatile __sig_atomic_t	g_signal;

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
	loop(data);
	rl_clear_history();
	gc_clear(data->gc);
	return (0);
}
