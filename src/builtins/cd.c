/*cd.c*/

#include "../../include/minishell.h"

static char	*get_env_from_list(char **env, const char *name)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

static void	update_env(char ***env, char *key, char *value)
{
	char	*tmp;
	char	*entry;

	(void)env; // para evitar warning, se não for usado
	tmp = ft_strjoin(key, "=");
	entry = ft_strjoin(tmp, value);
	free(tmp);
	// export_env(entry, env); // função que trata export ou sobrescreve env
	free(entry);
}

int	builtin_cd(char **argv, t_data *data)
{
	char	*path;
	char	*oldpwd;
	// char	cwd[1000]; // buffer para armazenar o diretório atual PATH_MAX

	if (!argv[1] || (argv[1][0] == '~' && argv[1][1] == '\0'))
		path = get_env_from_list(data->env, "HOME");
	else if (argv[1] && !ft_strncmp(argv[1], "-", 1))
	{
		path = get_env_from_list(data->env, "OLDPWD");
		if (!path)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
		ft_putendl_fd(path, 1); // printa novo path
	}
	else
		path = argv[1];
	if (!path || chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	oldpwd = getcwd(NULL, 0); // atualiza env
	if (oldpwd)
		update_env(&data->env, "OLDPWD", get_env_from_list(data->env, "PWD"));
	update_env(&data->env, "PWD", oldpwd);
	free(oldpwd);
	return (0);
}
