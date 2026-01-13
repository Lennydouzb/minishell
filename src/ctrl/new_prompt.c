/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:29:21 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/13 17:38:00 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_prompt(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}