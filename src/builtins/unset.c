/*unset.c*/

#include "../../include/minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	**remove_env_var(char **env, int index, t_data *data)
{
	char	**new_env;
	int		i;
	int		j;
	int		env_count;

	env_count = 0;
	while (env[env_count])
		env_count++;
	new_env = gc_malloc(data->gc, sizeof(char *) * env_count);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < env_count)
	{
		if (i != index)
		{
			new_env[j] = gc_strdup(env[i], data->gc);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	builtin_unset(char **argv, t_data *data)
{
	int	i;
	int	env_index;
	int	exit_status;

	if (!argv[1])
		return (0);
	exit_status = 0;
	i = 0;
	while (argv[++i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else
		{
			env_index = find_env_index(data->env, argv[i]);
			if (env_index != -1)
				data->env = remove_env_var(data->env, env_index, data);
		}
	}
	return (exit_status);
}
