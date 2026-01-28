/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:29:21 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/28 02:18:47 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_signal;

void	new_prompt(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = sig;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_child(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = sig;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = sig;
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}
