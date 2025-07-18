/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:41:10 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:55:53 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*join_path(const char *path, const char *cmd, t_gc *gc)
{
	char	*tmp;
	char	*full;

	tmp = gc_strjoin(path, "/", gc);
	full = gc_strjoin(tmp, cmd, gc);
	return (full);
}

static char	*search_paths_for_executable(char **pth, const char *cmd, t_gc *gc)
{
	char	*full_path;
	int		i;

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

char	*find_executable(const char *cmd, char **env, t_gc *gc)
{
	char	*path_env;
	char	**paths;
	char	*result_path;

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
