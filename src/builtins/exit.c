/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:35:27 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:35:28 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	get_exit_code(char *arg)
{
	long long	num;
	int			sign;
	int			i;

	if (!arg)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	if (arg[i] == '-')
		sign = -1;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i] && ft_isdigit(arg[i]))
	{
		num = num * 10 + (arg[i] - '0');
		if (num > 9223372036854775807LL)
			return (-1);
		i++;
	}
	return ((int)((num * sign) % 256));
}

static int	validate_exit_args(char **argv, t_data *data)
{
	if (!is_numeric(argv[1]) || get_exit_code(argv[1]) == -1)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		gc_clear(data->gc);
		exit(2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	builtin_exit(char **argv, t_data *data)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!argv[1])
	{
		gc_clear(data->gc);
		exit(data->exit_status);
	}
	if (validate_exit_args(argv, data) == 1)
		return (1);
	exit_code = get_exit_code(argv[1]);
	gc_clear(data->gc);
	exit(exit_code);
}
