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

static void	update_env(t_data *data, char *key, const char *value)
{
	int		env_index;
	char	*tmp;
	char	*final;

	tmp = ft_strjoin(key, "=");
	final = ft_strjoin(tmp, value);
	env_index = find_env_index(data->env, key);
	if (env_index != -1)
		data->env[env_index] = gc_strdup(final, data->gc);
	free(tmp);
	free(final);
}

static char	*resolve_cd_path(char **argv, t_data *data)
{
	char	*path;

	if (!argv[1] || (argv[1][0] == '~' && argv[1][1] == '\0'))
		return (get_env_from_list(data->env, "HOME"));
	else if (argv[1] && !ft_strncmp(argv[1], "-", 1))
	{
		path = get_env_from_list(data->env, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
		return (path);
	}
	return (argv[1]);
}

static void	update_pwd_and_oldpwd(t_data *data, const char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		update_env(data, "OLDPWD", oldpwd);
		update_env(data, "PWD", newpwd);
		free(newpwd);
	}
}

int	builtin_cd(char **argv, t_data *data)
{
	char	*path;
	char	*oldpwd;

	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	path = resolve_cd_path(argv, data);
	oldpwd = getcwd(NULL, 0);
	if (!path || chdir(path) != 0)
	{
		perror("minishell: cd");
		free(oldpwd);
		return (1);
	}
	update_pwd_and_oldpwd(data, oldpwd);
	free(oldpwd);
	return (0);
}
