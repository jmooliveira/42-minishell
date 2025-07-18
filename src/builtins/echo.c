/*echo.c*/

#include "../../include/minishell.h"

static int	skip_n_flags(char **argv, int *newline)
{
	int	i;
	int	j;

	i = 1;
	*newline = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		*newline = 0;
		i++;
	}
	return (i);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = skip_n_flags(argv, &newline);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
