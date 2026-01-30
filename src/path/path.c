/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:59:04 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 14:17:26 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(void)
{
	char	*path;
	char	*home;
	char	*final_path;
	char	*temp;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_strdup("minishell$ "));
	home = getenv("HOME");
	if (home && ft_strncmp(path, home, ft_strlen(home)) == 0)
	{
		final_path = ft_strjoin("~", path + ft_strlen(home));
	}
	else
	{
		final_path = ft_strdup(path);
	}
	free(path);
	temp = final_path;
	final_path = ft_strjoin(final_path, "$ ");
	free(temp);
	return (final_path);
}

int	change_path(t_cmd *cmd, char **env)
{
	int		result;
	char	*home_path;

	home_path = get_env_val("HOME", env);
	if (!cmd->args[1])
	{
		if (home_path && *home_path)
			result = chdir(home_path);
		else
			printf("minishell: cd: HOME not set\n");
	}
	else if (cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	else
		result = chdir(cmd->args[1]);
	if (result == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
