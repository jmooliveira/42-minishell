/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:35:35 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:39:09 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

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

static int	is_valid_export(const char *arg)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static void	update_or_add_variable(const char *arg, t_data *data)
{
	char	*equal_pos;
	char	*var_name;
	int		env_index;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		var_name = gc_substr(arg, 0, equal_pos - arg, data->gc);
		env_index = find_env_index(data->env, var_name);
		if (env_index != -1)
			data->env[env_index] = gc_strdup(arg, data->gc);
		else
			data->env = add_new_env(data->env, arg, data);
	}
	else
	{
		env_index = find_env_index(data->env, arg);
		if (env_index == -1)
			data->env = add_new_env(data->env, arg, data);
	}
}

static int	export_variable(const char *arg, t_data *data)
{
	if (!is_valid_export(arg))
		return (1);
	update_or_add_variable(arg, data);
	return (0);
}

int	builtin_export(char **argv, t_data *data)
{
	int	i;
	int	exit_status;

	if (!argv[1])
	{
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
	data->exit_status = exit_status;
	return (exit_status);
}
