/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PATH.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:10:48 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/14 23:40:51 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_PATH(t_cmd *cmd, char **env)
{
	char	**paths;
	char	*current_path;
	int		i;

	if (access(cmd->args[0], X_OK) == 0)
		return (ft_strdup(cmd->args[0]));
	i = 0;
	paths = ft_split(get_PATH_from_env(env) + 5, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		current_path = ft_strdup(paths[i]);
		current_path = ft_straddback(current_path, "/");
		current_path = ft_straddback(current_path, cmd->args[0]);
		if (access(current_path, X_OK) == 0)
			return (current_path);
		free(current_path);
		i++;
	}
	return (NULL);
}

char	*get_PATH_from_env(char **env)
{
	int i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i]);
		i++;
	}
	return (NULL);
}