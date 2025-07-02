#include "../../include/minishell.h"

void	handle_sigint(int sig)
{
    (void)sig;
    ft_putendl_fd("", STDOUT_FILENO);

}

void    handle_heredoc(int sig)
{
	(void)sig;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	close(STDIN_FILENO);
	g_signal = SIGINT;
}

void    handle_redo_line(int sig)
{
    (void)sig;
    ft_putendl_fd("", STDOUT_FILENO);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    g_signal = SIGINT;
}

void    handle_sigpipe(int sig)
{
    (void)sig;
}
