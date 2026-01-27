/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:36 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/28 00:25:48 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_signal = 0; // La seule et l'unique !

int	is_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strncmp(arg, "echo", 5) || !ft_strncmp(arg, "cd", 3)
		|| !ft_strncmp(arg, "pwd", 4) || !ft_strncmp(arg, "export", 7)
		|| !ft_strncmp(arg, "unset", 6) || !ft_strncmp(arg, "env", 4)
		|| !ft_strncmp(arg, "exit", 5))
		return (1);
	return (0);
}

static void	smartclose(t_cmd *cmd)
{
	if (cmd->fdin != 1 && cmd->fdin != 0 && cmd->fdin != 2)
		close(cmd->fdin);
	if (cmd->fdout != 1 && cmd->fdout != 0 && cmd->fdout != 2)
		close(cmd->fdout);
}

// void	printcmd(t_cmd *cmd)
//{
//	int	i = 0;
//
//	while (cmd)
//	{
//		i = 0;
//		printf("\n----------cmd------------\n");
//		printf("\nfdin = %d, fdout = %d\n", cmd->fdin, cmd->fdout);
//		while (cmd->raw[i])
//		{
//			printf ("\nraw[%d]= %s", i, cmd->raw[i]);
//			++i;
//		}
//		i = 0;
//		while (cmd->args[i])
//		{
//			printf ("\nargs[%d]= %s", i, cmd->args[i]);
//			++i;
//		}
//		cmd = cmd->next;
//	}
//}

char	**copy_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*write_prompt(void)
{
	char	*prompt_str;
	char	*input;

	prompt_str = get_path();
	input = readline(prompt_str);
	free(prompt_str);
	if (!input)
	{
		write(1, "exit\n", 5);
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_cmd	*cmd;
	pid_t	pid;
	int		status;
	char	**local_env;
	int		g_status;

	(void)ac;
	(void)av;
	g_status = 0;
	local_env = copy_env(env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = write_prompt();
		signal(SIGINT, new_prompt);
		cmd = parse(input, local_env, g_status);
		free(input);
		if (g_signal == SIGINT)
		{
			g_status = 130;
			g_signal = 0;
			continue ;
		}
		if (!cmd)
			perror("error");
		signal(SIGINT, sig_child);
		while (cmd)
		{
			if (!cmd->args || !cmd->args[0])
			{
				cmd = cmd->next;
				continue ;
			}
			if (is_builtin(cmd->args[0]))
				g_status = execute_builtin(cmd, local_env);
			else
			{
				pid = fork();
				if (pid == 0)
				{
					if (cmd->fdin != STDIN_FILENO)
						dup2(cmd->fdin, STDIN_FILENO);
					if (cmd->fdout != STDOUT_FILENO)
						dup2(cmd->fdout, STDOUT_FILENO);
					smartclose(cmd);
					execve(cmd->path, cmd->args, local_env);
					exit(1);
				}
			}
			smartclose(cmd);
			cmd = cmd->next;
		}
		if (pid != -1)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_status = 128 + WTERMSIG(status);
		}
		while (wait(NULL) > 0)
			;
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
