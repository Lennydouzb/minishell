/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:31:22 by ldesboui          #+#    #+#             */
/*   Updated: 2026/02/05 01:31:48 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_signal;

void	print_free(char *line, int *fd)
{
	ft_putendl_fd(line, fd[1]);
	free(line);
}

int	heredoc_event_hook(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

char	*ft_readline_no_tty(void)
{
	char	*line;
	char	buf[2];
	int		ret;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	buf[1] = '\0';
	while (1)
	{
		ret = read(STDIN_FILENO, buf, 1);
		if (ret <= 0)
			break ;
		if (buf[0] == '\n')
			break ;
		line = ft_straddback(line, buf);
	}
	if (ret <= 0 && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
