/*export.c*/

#include "../../include/minishell.h"

static int is_valid_identifier(const char *str)
{
	int i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[0] == '=' || (str[i] == '=' && i == 0))
		return (0);
	return (1);
}

static void	print_export_format(char **env)
{
	int		i;
	char	*equal_pos;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		equal_pos = ft_strchr(env[i], '=');
		if (equal_pos)
		{ // Imprime nome da variável
			write(STDOUT_FILENO, env[i], equal_pos - env[i]);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(equal_pos + 1, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}

static int	find_env_index(char **env, const char *name)
{
	int		i;
	size_t	name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, name_len)
			&& (env[i][name_len] == '=' || env[i][name_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static char	**add_new_env(char **env, const char *new_var, t_data *data)
{
	char	**new_env;
	int		i;
	int		env_count;

	env_count = 0;
	while (env[env_count])
		env_count++;
	new_env = gc_malloc(data->gc, sizeof(char *) * (env_count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		new_env[i] = gc_strdup(env[i], data->gc);
		i++;
	}
	new_env[i] = gc_strdup(new_var, data->gc);
	new_env[i + 1] = NULL;
	return (new_env);
}

static int	export_variable(const char *arg, t_data *data)
{
	char	*equal_pos;
	char	*var_name;
	int		env_index;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	equal_pos = ft_strchr(arg, '=');
	if (equal_pos) // Tem valor para atribuir
	{
		var_name = gc_substr(arg, 0, equal_pos - arg, data->gc);
		env_index = find_env_index(data->env, var_name);
		if (env_index != -1) // Atualiza variável existente
			data->env[env_index] = gc_strdup(arg, data->gc);
		else // Adiciona nova variável
			data->env = add_new_env(data->env, arg, data);
	}
	else // Só o nome da variável, sem valor
	{
		env_index = find_env_index(data->env, arg);
		if (env_index == -1) // Adiciona variável sem valor
			data->env = add_new_env(data->env, arg, data);
	} // Se já existe, não faz nada
	return (0);
}

int	builtin_export(char **argv, t_data *data)
{
	int	i;
	int	exit_status;

	if (!argv[1])
	{ // Sem argumentos, imprime todas as variáveis
		print_export_format(data->env);
		return (0);
	}
	exit_status = 0;
	i = 1;
	while (argv[i])
	{
		if (export_variable(argv[i], data) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
