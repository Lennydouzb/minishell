/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:34:50 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/28 00:40:29 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	smartclose(t_cmd *cmd)
{
	if (cmd->fdin != 1 && cmd->fdin != 0 && cmd->fdin != 2)
		close(cmd->fdin);
	if (cmd->fdout != 1 && cmd->fdout != 0 && cmd->fdout != 2)
		close(cmd->fdout);
}

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

void	wait_and_update_status(pid_t last_pid, int *g_status)
{
	int	status;

	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			*g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*g_status = 128 + WTERMSIG(status);
	}
	while (wait(NULL) > 0)
		;
}
