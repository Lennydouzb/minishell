/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:34:53 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/05 01:50:48 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
