/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:36 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/15 16:02:46 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_status = 0;

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

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_cmd	*cmd;
	pid_t	pid;
	int		status;
	char	**local_env;

	(void)(ac);
	(void)av;
	local_env = copy_env(env);
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline(get_path());
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*input)
			add_history(input);
		cmd = parse(input, local_env);
		free(input);
		if (!cmd)
			perror("error");
		while (cmd)
		{
			if (!cmd->args || !cmd->args[0])
			{
				cmd = cmd->next;
				continue ;
			}
			if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
				change_path(cmd);
			else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
				ft_echo(cmd);
			else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
				ft_pwd(cmd);
			else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
				ft_env(cmd, local_env);
			else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
				ft_exit(cmd);
			else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
				ft_export(cmd, &local_env);
			else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
				ft_unset(cmd, &local_env);
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
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		while (wait(NULL) > 0)
			;
	}
	return (0);
}
