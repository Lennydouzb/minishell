/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:37:26 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/06 20:17:18 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* minishell/src/cmd_loop.c */

#include "../includes/minishell.h"

static void	handle_exec_error(char *path, char *cmd_name, t_cmd *first,
		char **env)
{
	struct stat	sb;

	no_acces_error(path, cmd_name, first, env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		ft_putendl_fd(": Is a directory", 2);
	else if (access(path, X_OK) == -1)
		ft_putendl_fd(": Permission denied", 2);
	else
		perror(": execution failed");
	free_cmds(first);
	ft_free_tab(env);
	exit(126);
}

static void	loop_close(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd->next;
	while (tmp)
	{
		smartclose(tmp);
		tmp = tmp->next;
	}
}

static void	child_process(t_cmd *cmd, char **env, t_cmd *first)
{
	int	ret;

	signal(SIGQUIT, SIG_DFL);
	loop_close(cmd);
	if (cmd->fdin == -1 || cmd->fdout == -1)
		exit(1);
	close_standard(cmd);
	if (is_builtin(cmd->args[0]))
	{
		ret = execute_builtin(cmd, &env, first);
		free_and_exit(ret, first, env);
	}
	smartclose(cmd);
	if (!cmd->args[0])
		free_and_exit(0, first, env);
	if (cmd->args[0] && cmd->args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: '' : command not found\n", 2);
		free_and_exit(127, first, env);
	}
	if (!cmd->path)
		handle_exec_error(NULL, cmd->args[0], first, env);
	execve(cmd->path, cmd->args, env);
	handle_exec_error(cmd->path, cmd->args[0], first, env);
}

static int	cmd_loop(t_cmd *cmd, char ***env, int *status, t_cmd *first)
{
	int	pid;

	pid = -1;
	if (is_builtin(cmd->args[0]) && !cmd->next && cmd == first)
	{
		if (cmd->fdin == -1 || cmd->fdout == -1)
			*status = 1;
		else
			*status = execute_builtin(cmd, env, first);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd->fdin == -1 || cmd->fdout == -1)
				exit(1);
			child_process(cmd, *env, first);
		}
	}
	return (pid);
}

pid_t	exec_cmd_loop(t_cmd *cmd, char ***env, int *status)
{
	pid_t	pid;
	t_cmd	*first;

	pid = -1;
	first = cmd;
	while (cmd)
	{
		if (!cmd->args)
		{
			smartclose(cmd);
			cmd = cmd->next;
			continue ;
		}
		pid = cmd_loop(cmd, env, status, first);
		smartclose(cmd);
		cmd = cmd->next;
	}
	return (pid);
}
