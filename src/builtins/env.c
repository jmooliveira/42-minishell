/*env.c*/

#include "../../include/minishell.h"

int	builtin_env(char **envp)
{
	int	i;

	if (!envp)
		return (1);

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '=')) // só imprime se tiver '='
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
