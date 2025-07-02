#include "../../include/minishell.h"

void	heredoc_signal(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	interactive_signal(void)
{
	signal(SIGINT, handle_redo_line);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	setup_signals(int pid)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, handle_sigpipe);
	}
	else
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_IGN);
	}
}