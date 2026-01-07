/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:36 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/07 11:20:55 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	(void)(ac);
	(void)av;
	t_cmd	*cmd;

	while (1)
	{
		input = readline("minishell : ");
		cmd = parse(input);
		if (!cmd)
			perror("error");
		char *args[] = {cmd->args[0], NULL};
		pid_t pid = fork();
		if (pid ==  0)
		{
			dup2(cmd->fdin, STDOUT_FILENO);
			close(cmd->fdin);
			execve(strcat(strdup("/bin/"), cmd->args[0]), args, env);
		}
	}
	return (0);
}
