/*exec_operators.c*/

#include "../../include/minishell.h"

int execute_and_or(t_ast *node, t_data *data)
{
    int     status;
    t_ast   *left;
    t_ast   *right;

    left = node->left;
    right = node->right;
    status = exec_ast(left, data);
    if (node->type == AND)
    {
        if (status == 0)
            return (exec_ast(right, data));
        return (status);

    }
    if (node->type == OR)
    {
        if (status != 0)
            return (exec_ast(right, data));
        return (status);

    }
    return (data->exit_status);
}

int    exec_pipe_child(t_ast *node, t_data *data, int *pipefd, bool is_left)
{
    int status;

    if (is_left)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
    }
    status = exec_ast(node, data);
    exit(status);
}

int    execute_pipe(t_ast *node, t_data *data)
{
    int     pipefd[2];
    pid_t   pid_left;
    pid_t   pid_right;
    int     status;

    if (pipe(pipefd) == -1)
        return (perror("pipe"), 1);
    pid_left = fork();
    if (pid_left == -1)
        return (perror("fork"), 1);
    if (pid_left == 0)
        exec_pipe_child(node->left, data, pipefd, true);
    pid_right = fork();
    if (pid_right == -1)
        return (perror("fork"), 1);
    if (pid_right == 0)
        exec_pipe_child(node->right, data, pipefd, false);
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid_left, &status, 0);
    waitpid(pid_right, &status, 0);
    data->exit_status = WEXITSTATUS(status);
    return (data->exit_status);
}

int execute_subshell(t_ast *node, t_data *data)
{
    int     status;
    pid_t   subshell;

    subshell = fork();
    if (subshell == -1)
        return (perror("fork"), 1);
    if (subshell == 0)
    {
        status = exec_ast(node->left, data);
        exit(status);
    }
    waitpid(subshell, &status, 0);
    data->exit_status = WEXITSTATUS(status);
    return (data->exit_status);
}
