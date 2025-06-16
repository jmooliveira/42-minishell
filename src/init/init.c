/*init.c*/

#include "../../include/minishell.h"

int	count_envlen(char **ev)
{
	int len;

	len = 0;
	while (ev[len])
		len++;
	return (len);
}

t_data	*init_data(char **ev)
{
	t_data	*data;
	t_gc	*gc;
	
	gc = gc_init();
	data = gc_malloc(gc, sizeof(t_data));
	if (!data)
	{
		ft_printf("Erro: in malloc\n");
		return (NULL);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->env = copy_env(ev, gc); // copia o env para o data->env, adicionei para pegar envp
	data->env_len = count_envlen(ev);
	data->prompt = "minishell$ ";
	data->gc = gc;
	return (data);
}

char	**copy_env(char **ev, t_gc *gc)
{
	char	**env_copy;
	int		i;

	env_copy = gc_malloc(gc, sizeof(char *) * (count_envlen(ev) + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (ev[i])
	{
		env_copy[i] = gc_strdup(ev[i], gc);
		if (!env_copy[i])
			return (NULL);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}