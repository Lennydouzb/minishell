/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:34:53 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/06 20:17:53 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	no_acces_error(char *path, char *cmd_name, t_cmd *first, char **env)
{
	if (!path || access(path, F_OK) == -1)
	{
		if (ft_strchr(cmd_name, '/'))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_name, 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
		else
		{
			ft_putstr_fd(cmd_name, 2);
			ft_putendl_fd(": command not found", 2);
		}
		free_cmds(first);
		ft_free_tab(env);
		exit(127);
	}
}

void	close_standard(t_cmd *cmd)
{
	if (cmd->fdin != STDIN_FILENO)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
	}
	if (cmd->fdout != STDOUT_FILENO)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
		cmd->fdout = STDOUT_FILENO;
	}
}

void	free_and_exit(int exit_code, t_cmd *first, char **env)
{
	free_cmds(first);
	ft_free_tab(env);
	exit(exit_code);
}
