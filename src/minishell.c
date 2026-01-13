/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:36 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/13 17:39:47 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_cmd	*cmd;
	pid_t	pid;

	(void)(ac);
	(void)av;
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
		cmd = parse(input);
		free(input);
		if (!cmd)
			perror("error");
		while (cmd)
		{
			if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
				change_path(cmd);
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
					execve(cmd->path, cmd->args, env);
					exit(1);
				}
				else
					smartclose(cmd);
			}
			cmd = cmd->next;
		}
		while (wait(NULL) > 0)
			;
	}
	return (0);
}
