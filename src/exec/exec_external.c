/*exec_external.c*/

#include "../../include/minishell.h"

// Protótipos de funções auxiliares (você pode adaptar para seu GC)
char	*get_env_value(const char *key, char **env);
char	**ft_split(char const *s, char c);
char	*gc_strjoin(const char *s1, const char *s2, t_gc *gc);
char	*gc_strdup(const char *s, t_gc *gc);
void	free_split(char **arr);

void free_split(char **split)
{
    int i = 0;
    if (!split)
        return;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

// Função que junta caminho + '/' + comando
static char *join_path(const char *path, const char *cmd, t_gc *gc)
{
	char *tmp;
	char *full;

	tmp = gc_strjoin(path, "/", gc);
	full = gc_strjoin(tmp, cmd, gc);
	// tmp é gerenciado pelo gc, então não precisa free
	return (full);
}

// Busca executável no PATH (retorna string alocada no gc ou NULL)
static char *find_executable(const char *cmd, char **env, t_gc *gc)
{
	char **paths;
	char *path_env;
	char *full_path;
	int i;

	// Se o comando já tem '/' é caminho absoluto/relativo, retorna duplicado
	if (ft_strchr(cmd, '/'))
		return (gc_strdup(cmd, gc));

	path_env = get_env_value("PATH", env);
	if (!path_env)
		return (NULL);

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);

	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd, gc);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths); // libera split tradicional
			return (full_path);
		}
		i++;
	}
	free_split(paths);
	return (NULL);
}

// Executa comando externo com fork e execve, retorna status
int	execute_external(t_ast *node, t_data *data, t_gc *gc)
{
	pid_t		pid;
	int			status;
	struct stat	sb;
	char		*cmd_path;

	if (!node || !node->args || !node->args[0])
		return (1);
	if (ft_strchr(node->args[0], '/'))
	{
		cmd_path = gc_strdup(node->args[0], gc);
		if (access(cmd_path, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(node->args[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			data->exit_status = 127;
			return (127);
		}
	}
	else
	{

		cmd_path = find_executable(node->args[0], data->env, gc);
		if (!cmd_path || access(cmd_path, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(node->args[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			data->exit_status = 127;
			return (127);
		}
	}
	if (stat(cmd_path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		data->exit_status = 126;
		return (126);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		data->exit_status = 126;
		return (126);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, node->args, data->env);
		perror("minishell");
		exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_status = 128 + WTERMSIG(status);
		else
			data->exit_status = 1;
	}
	else
	{
		perror("minishell: fork");
		data->exit_status = 1;
	}

	return (data->exit_status);
}

