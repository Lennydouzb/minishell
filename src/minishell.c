/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:36 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/07 17:51:41 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	char	*input;
	(void)(ac);
	(void)av;
	t_cmd	*cmd;

	while (1)
	{
		input = readline("minishell :");
		cmd = parse(input);
		free(input);
		if (!cmd)
			perror("error");
		pid_t pid = fork();
		if (pid ==  0)
		{
			//dup2(cmd->fdin, STDIN_FILENO);
			close(cmd->fdin);
			//if (access(cmd->path, F_OK))
			execve(cmd->path, cmd->args, env);
			exit(1);
		}
		else
			wait(NULL);
	}
	return (0);
}
