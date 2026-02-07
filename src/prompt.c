/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:39:51 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/07 12:55:21 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_heredoc_prompt(void)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline("> ");
	else
		line = ft_readline_no_tty();
	return (line);
}

static char	*no_interface_prompt(void)
{
	char	*gnl_ret;
	char	*input;

	gnl_ret = get_next_line(STDIN_FILENO);
	if (!gnl_ret)
		return (NULL);
	input = ft_strtrim(gnl_ret, "\n");
	free(gnl_ret);
	return (input);
}

char	*write_prompt(void)
{
	char	*prompt_str;
	char	*input;

	if (isatty(STDIN_FILENO))
	{
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
	else
	{
		input = no_interface_prompt();
		return (input);
	}
}
