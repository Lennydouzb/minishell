/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:37:26 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 13:59:42 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_process(t_cmd *cmd, char **env)
{
	if (cmd->fdin != STDIN_FILENO)
		dup2(cmd->fdin, STDIN_FILENO);
	if (cmd->fdout != STDOUT_FILENO)
		dup2(cmd->fdout, STDOUT_FILENO);
	smartclose(cmd);
	if (cmd->path)
		execve(cmd->path, cmd->args, env);
	exit(1);
}

pid_t	exec_cmd_loop(t_cmd *cmd, char ***env, int *status)
{
	pid_t	pid;

	pid = -1;
	while (cmd)
	{
		if (!cmd->args || !cmd->args[0])
		{
			cmd = cmd->next;
			continue ;
		}
		if (is_builtin(cmd->args[0]))
			*status = execute_builtin(cmd, env);
		else
		{
			pid = fork();
			if (pid == 0)
				child_process(cmd, *env);
		}
		smartclose(cmd);
		cmd = cmd->next;
	}
	return (pid);
}
