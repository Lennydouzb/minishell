/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:36 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/28 03:36:45 by fgarnier         ###   ########.fr       */
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

static void	process_cmd(t_cmd *cmd, char **env, int *status)
{
	pid_t	pid;

	if (g_signal == SIGINT)
	{
		*status = 130;
		g_signal = 0;
		return ;
	}
	if (!cmd)
	{
		perror("error");
		return ;
	}
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
	int		g_status;

	local_env = init_shell(ac, av, env, &g_status);
	while (1)
	{
		signal(SIGINT, new_prompt);
		input = write_prompt();
		if (!input)
			break ;
		cmd = parse(input, local_env, g_status);
		free(input);
		process_cmd(cmd, local_env, &g_status);
	}
	return (0);
}

int	execute_builtin(t_cmd *cmd, char **local_env)
{
	int	res;

	res = 1;
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		res = change_path(cmd);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		res = ft_echo(cmd);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		res = ft_pwd(cmd);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		res = ft_env(cmd, local_env);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		res = ft_export(cmd, &local_env);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		res = ft_unset(cmd, &local_env);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_exit(cmd);
	return (res);
}
