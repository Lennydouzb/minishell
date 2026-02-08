/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:10:48 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/05 01:55:54 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_all_paths(char ***paths, char **path_var, char **env)
{
	*path_var = get_env_path_from_env(env);
	if (!(*path_var))
		return ;
	*paths = ft_split(*path_var + 5, ':');
	if (!(*paths))
		return ;
}

static char	*get_current_path(char **paths, t_cmd *cmd, int *i)
{
	char	*current_path;

	current_path = ft_strdup(paths[*i]);
	current_path = ft_straddback(current_path, "/");
	current_path = ft_straddback(current_path, cmd->args[0]);
	return (current_path);
}

char	*get_env_path(t_cmd *cmd, char **env, char **paths)
{
	char	*curr;
	char	*p_var;
	int		i;

	if (ft_strchr(cmd->args[0], '/'))
		return (ft_strdup(cmd->args[0]));
	p_var = NULL;
	paths = NULL;
	get_all_paths(&paths, &p_var, env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		curr = get_current_path(paths, cmd, &i);
		if (is_valid_exec(curr))
		{
			ft_free_tab(paths);
			return (curr);
		}
		free(curr);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}

char	*get_env_path_from_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*get_env_val(char *var, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return ("");
}
