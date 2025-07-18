/*exec_external.c*/

#include "../../include/minishell.h"

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

static char *join_path(const char *path, const char *cmd, t_gc *gc)
{
	char *tmp;
	char *full;

	tmp = gc_strjoin(path, "/", gc);
	full = gc_strjoin(tmp, cmd, gc);
	return (full);
}

static char *search_paths_for_executable(char **pth, const char *cmd, t_gc *gc)
{
    char *full_path;
    int  i;

    i = 0;
    while (pth[i])
    {
        full_path = join_path(pth[i], cmd, gc);
        if (access(full_path, X_OK) == 0)
        {
            return (full_path);
        }
        i++;
    }
    return (NULL);
}

char *find_executable(const char *cmd, char **env, t_gc *gc)
{
    char *path_env;
    char **paths;
    char *result_path;

    if (ft_strchr(cmd, '/'))
        return (gc_strdup(cmd, gc));
    path_env = get_env_value("PATH", env);
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    result_path = search_paths_for_executable(paths, cmd, gc);
    free_split(paths);
    return (result_path);
}

int	print_error_not_found(t_data *data, t_ast *node, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(node->args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = 127;
	return(data->exit_status);
}

int	print_error(t_data *data, char *cmd_path, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_path, STDERR_FILENO);
	ft_putendl_fd(": ", STDERR_FILENO);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror("");
	data->exit_status = 126;
	return (data->exit_status);
}

static char	*get_and_check_cmd_path(t_ast *node, t_data *data, t_gc *gc)
{
    char    *cmd_path;

    if (ft_strchr(node->args[0], '/'))
    {
        cmd_path = gc_strdup(node->args[0], gc);
        if (access(cmd_path, F_OK) != 0)
        {
            print_error_not_found(data, node, "No such file or directory");
            return (NULL);
        }
    }
    else
    {
        cmd_path = find_executable(node->args[0], data->env, gc);
        if (!cmd_path || access(cmd_path, F_OK) != 0)
        {
            print_error_not_found(data, node, "command not found");
            return (NULL);
        }
    }
    return (cmd_path);
}

static void handle_child_process(char *cmd_path, t_ast *node, t_data *data)
{
    setup_signals(0);
    execve(cmd_path, node->args, data->env);
    perror("minishell");
    exit(126);
}

static void handle_parent_process(pid_t pid, t_data *data)
{
    int status;
    int sig;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        data->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        sig = WTERMSIG(status);
        if (sig == SIGQUIT)
            printf("Quit (core dumped)\n");
        data->exit_status = 128 + WTERMSIG(status);
    }
    else
        data->exit_status = 1;
}

int execute_external(t_ast *node, t_data *data, t_gc *gc)
{
    pid_t       pid;
    struct stat sb;
    char        *cmd_path;

    if (!node || !node->args || !node->args[0])
        return (1);
    cmd_path = get_and_check_cmd_path(node, data, gc);
    if (!cmd_path)
        return (data->exit_status);
    if (stat(cmd_path, &sb) == 0 && S_ISDIR(sb.st_mode))
        return (print_error(data, cmd_path, "Is a directory"));
    if (access(cmd_path, X_OK) != 0)
        return (print_error(data, cmd_path, NULL));
    pid = fork();
    if (pid == -1)
    {
        perror("minishell: fork");
        data->exit_status = 1;
    }
    else if (pid == 0)
        handle_child_process(cmd_path, node, data);
    else
        handle_parent_process(pid, data);
    return (data->exit_status);
}
