/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:47:38 by ldesboui          #+#    #+#             */
/*   Updated: 2026/02/03 20:15:36 by ldesboui         ###   ########.fr       */
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
