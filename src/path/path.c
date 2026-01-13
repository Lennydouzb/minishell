/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:59:04 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/13 17:16:56 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(void)
{
	char	*path;
	char	*home;
	char	*final_path;
	char	*short_path;

	path = getcwd(NULL, 0);
	home = getenv("HOME");
	if (ft_strnstr(path, home, ft_strlen(home)))
	{
		short_path = ft_strdup(path + ft_strlen(home));
		final_path = ft_strjoin("~", short_path);
		free(short_path);
	}
	else
		final_path = ft_strdup(path);
	free(path);
	path = ft_strjoin(final_path, "$ ");
	free(final_path);
	return (path);
}

void	change_path(t_cmd *cmd)
{
	if (!cmd->args[1])
		chdir(getenv("HOME"));
	else if (cmd->args[2])
		ft_putendl_fd("minishell : cd: too many arguments", 2);
	else if (chdir(cmd->args[1]) == -1)
		perror("minishell: cd");
}