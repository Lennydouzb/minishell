/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:37:26 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/31 03:52:49 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* minishell/src/cmd_loop.c */

#include "../includes/minishell.h"

static void	handle_exec_error(char *path, char *cmd_name)
{
	struct stat	sb;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	if (!path || access(path, F_OK) == -1)
	{
		if (ft_strchr(cmd_name, '/'))
			ft_putendl_fd(": No such file or directory", 2);
		else
			ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	exit(0);
}

static void	child_process(t_cmd *cmd, char **env)
{
	t_cmd	*tmp;

	tmp = cmd->next;
	while (tmp)
	{
		smartclose(tmp);
		tmp = tmp->next;
	}
	if (cmd->fdin == -1 || cmd->fdout == -1)
		exit(1);
	if (cmd->fdin != STDIN_FILENO)
		dup2(cmd->fdin, STDIN_FILENO);
	if (cmd->fdout != STDOUT_FILENO)
		dup2(cmd->fdout, STDOUT_FILENO);
	smartclose(cmd);
	if (!cmd->args[0])
		exit(0);
	if (!cmd->path)
		handle_exec_error(NULL, cmd->args[0]);
	execve(cmd->path, cmd->args, env);
	handle_exec_error(cmd->path, cmd->args[0]);
}

pid_t	exec_cmd_loop(t_cmd *cmd, char ***env, int *status)
{
	pid_t	pid;
	t_cmd	*first;

	pid = -1;
	first = cmd;
	while (cmd)
	{
		if (!cmd->args || !cmd->args[0])
		{
			if (cmd->fdin == -1 || cmd->fdout == -1)
				*status = 1;
			cmd = cmd->next;
			continue ;
		}
		if (is_builtin(cmd->args[0]) && !cmd->next && cmd == first)
		{
			if (cmd->fdin == -1 || cmd->fdout == -1)
				*status = 1;
			else
				*status = execute_builtin(cmd, env);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (cmd->fdin == -1 || cmd->fdout == -1)
					exit(1);
				if (is_builtin(cmd->args[0]))
					exit(execute_builtin(cmd, env));
				child_process(cmd, *env);
			}
		}
		smartclose(cmd);
		cmd = cmd->next;
	}
	return (pid);
}
