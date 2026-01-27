/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:48:28 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/28 00:13:14 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

extern int	g_signal;

int	handle_heredoc(char *delimiter, char **env, int status)
{
	int		fd[2];
	char	*line;
	int		stdin_backup;

	if (pipe(fd) == -1)
		return (-1);
	stdin_backup = dup(STDIN_FILENO);
	signal(SIGINT, sig_heredoc);
	g_signal = 0;
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT || !line)
		{
			if (g_signal == SIGINT)
			{
				dup2(stdin_backup, STDIN_FILENO);
				close(stdin_backup);
				if (line)
					free(line);
				close(fd[0]);
				close(fd[1]);
				return (-2);
			}
			close(stdin_backup);
			free(line);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			close(stdin_backup);
			free(line);
			break ;
		}
		line = expand_variables(line, env, status);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

int	redirect(char *flag, char *file, char **env, int status)
{
	int	fd;

	if (ft_strncmp(flag, ">>", 3) == 0)
		return (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (ft_strncmp(flag, "<<", 3) == 0)
		fd = handle_heredoc(file, env, status);
	if (ft_strncmp(flag, ">", 2) == 0)
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (ft_strncmp(flag, "<", 2) == 0)
		fd = open(file, O_RDONLY);
	return (fd);
}
