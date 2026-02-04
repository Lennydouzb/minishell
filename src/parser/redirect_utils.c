/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:31:22 by ldesboui          #+#    #+#             */
/*   Updated: 2026/02/04 15:51:55 by fgarnier         ###   ########.fr       */
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
