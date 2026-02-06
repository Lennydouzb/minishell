/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:36 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/06 09:40:31 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_signal = 0;

static char	**init_shell(int ac, char **av, char **env, int *status)
{
	char	**local_env;

	(void)ac;
	(void)av;
	*status = 0;
	signal(SIGQUIT, SIG_IGN);
	local_env = copy_env(env);
	return (local_env);
}

static void	process_cmd(t_cmd *cmd, char ***env, int *status)
{
	pid_t	pid;

	if (!cmd)
		return ;
	if (cmd->fdin == -1 || cmd->fdout == -1)
		*status = 1;
	signal(SIGINT, sig_child);
	pid = exec_cmd_loop(cmd, env, status);
	wait_and_update_status(pid, status);
	if (g_signal == SIGINT)
		g_signal = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_cmd	*cmd;
	char	**local_env;
	int		exit_status;

	local_env = init_shell(ac, av, env, &exit_status);
	while (1)
	{
		signal(SIGINT, new_prompt);
		input = write_prompt();
		if (!input)
			break ;
		cmd = process_parsing(&exit_status, input, local_env);
		process_cmd(cmd, &local_env, &exit_status);
		free_cmds(cmd);
	}
	ft_free_tab(local_env);
	rl_clear_history();
	return (exit_status);
}

int	execute_builtin(t_cmd *cmd, char ***local_env, t_cmd *first)
{
	int	res;

	res = 1;
	if (ft_strncmp(cmd->args[0], "cd\0", 3) == 0)
		res = change_path(cmd, local_env);
	else if (ft_strncmp(cmd->args[0], "echo\0", 5) == 0)
		res = ft_echo(cmd);
	else if (ft_strncmp(cmd->args[0], "pwd\0", 4) == 0)
		res = ft_pwd(cmd);
	else if (ft_strncmp(cmd->args[0], "env\0", 4) == 0)
		res = ft_env(cmd, *local_env);
	else if (ft_strncmp(cmd->args[0], "export\0", 7) == 0)
		res = ft_export(cmd, local_env);
	else if (ft_strncmp(cmd->args[0], "unset\0", 6) == 0)
		res = ft_unset(cmd, local_env);
	else if (ft_strncmp(cmd->args[0], "exit\0", 5) == 0)
		ft_exit(cmd, local_env, first);
	return (res);
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;
	int		is_first;

	is_first = 1;
	i = 0;
	while (cmd)
	{
		tmp = cmd->next;
		free_cmds_loop(cmd, &i, &is_first);
		free(cmd);
		cmd = tmp;
		is_first = 0;
	}
}
