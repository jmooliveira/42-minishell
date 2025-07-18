/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:38:17 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:39:07 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_export_format(char **env)
{
	int		i;
	char	*equal_pos;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		equal_pos = ft_strchr(env[i], '=');
		if (equal_pos)
		{
			write(STDOUT_FILENO, env[i], equal_pos - env[i]);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(equal_pos + 1, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}

char	**add_new_env(char **env, const char *new_var, t_data *data)
{
	char	**new_env;
	int		i;
	int		env_count;

	env_count = 0;
	while (env[env_count])
		env_count++;
	new_env = gc_malloc(data->gc, sizeof(char *) * (env_count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		new_env[i] = gc_strdup(env[i], data->gc);
		i++;
	}
	new_env[i] = gc_strdup(new_var, data->gc);
	new_env[i + 1] = NULL;
	return (new_env);
}
