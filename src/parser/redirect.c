/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:48:28 by ldesboui          #+#    #+#             */
/*   Updated: 2026/02/05 01:44:09 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_signal;

static int	exit_sigint(int *fd, char *line, char *delim)
{
	rl_event_hook = NULL;
	if (line)
		free(line);
	if (delim)
		free(delim);
	close(fd[0]);
	close(fd[1]);
	return (-2);
}

static void	process_line(char *line, int fd_out, char **env, int status)
{
	line = expand_variables(line, env, status, 0);
	ft_putendl_fd(line, fd_out);
	free(line);
}

static int	heredoc_loop(int *fd, char *delim, char **env, int status)
{
	char	*line;

	while (1)
	{
		rl_event_hook = heredoc_event_hook;
		line = get_heredoc_prompt();
		rl_event_hook = 0;
		if (g_signal == SIGINT)
			return (exit_sigint(fd, line, delim));
		if (!line)
			break ;
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (env != NULL)
			process_line(line, fd[1], env, status);
		else
			print_free(line, fd);
	}
	rl_event_hook = NULL;
	return (0);
}

int	handle_heredoc(char *raw_delim, char **env, int status)
{
	int		fd[2];
	int		ret;
	char	*delim;
	int		quoted;

	if (pipe(fd) == -1)
		return (-1);
	quoted = (ft_isinstring(raw_delim, '"') || ft_isinstring(raw_delim, '\''));
	delim = remove_quotes(ft_strdup(raw_delim));
	signal(SIGINT, sig_heredoc);
	if (quoted == 1)
		ret = heredoc_loop(fd, delim, NULL, status);
	else
		ret = heredoc_loop(fd, delim, env, status);
	if (ret == -2)
		return (-2);
	close(fd[1]);
	free(delim);
	return (fd[0]);
}

int	redirect(char *flag, char *file, char **env, int status)
{
	int		fd;
	char	*cleaned_file;

	fd = -1;
	if (ft_strncmp(flag, "<<", 3) == 0)
		fd = handle_heredoc(file, env, status);
	cleaned_file = expand_variables(ft_strdup(file), env, status, 0);
	cleaned_file = remove_quotes(cleaned_file);
	if (ft_strncmp(flag, ">>", 3) == 0)
		fd = open(cleaned_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strncmp(flag, ">", 2) == 0)
		fd = open(cleaned_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strncmp(flag, "<", 2) == 0)
		fd = open(cleaned_file, O_RDONLY);
	free(cleaned_file);
	if (fd == -1 && ft_strncmp(flag, "<<", 2) != 0)
	{
		perror("minishell");
		return (-1);
	}
	return (fd);
}
