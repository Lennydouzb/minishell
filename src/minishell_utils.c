/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:47:38 by ldesboui          #+#    #+#             */
/*   Updated: 2026/02/04 16:53:49 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_signal;

t_cmd	*process_parsing(int *exit_status, char *input, char **l_env)
{
	t_cmd	*cmd;

	if (g_signal == SIGINT)
	{
		*exit_status = 130;
		g_signal = 0;
	}
	cmd = parse(input, l_env, *exit_status);
	if (g_signal == SIGINT)
	{
		*exit_status = 130;
		g_signal = 0;
		free(input);
		if (cmd)
			free_cmds(cmd);
		return (NULL);
	}
	free(input);
	if (!cmd)
	{
		*exit_status = 2;
		return (NULL);
	}
	return (cmd);
}

void	free_cmds_loop(t_cmd *cmd, int *i, int *is_first)
{
	if (cmd->args)
	{
		*i = 0;
		while (cmd->args[*i])
		{
			free(cmd->args[*i]);
			cmd->args[*i] = NULL;
			++(*i);
		}
		free(cmd->args);
		cmd->args = NULL;
	}
	if (*is_first && cmd->raw)
	{
		*i = 0;
		while (cmd->raw[*i])
			free(cmd->raw[(*i)++]);
		free(cmd->raw);
	}
	if (cmd->path)
		free(cmd->path);
}
