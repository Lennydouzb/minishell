/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:45:33 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/06 10:23:03 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

static void	free_raw(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		++i;
	}
}

static void	error_free(char **raw, char *type)
{
	syntax_error(type);
	free_raw(raw);
}

static void	redirection_error(char **raw, int i)
{
	if (raw[i + 1])
		error_free(raw, raw[i + 1]);
	else
		error_free(raw, "newline");
}

int	check_syntax_error(char **raw)
{
	int	i;

	i = -1;
	if (raw[0] && !ft_strncmp(raw[0], "|", 2))
	{
		error_free(raw, "|");
		return (1);
	}
	while (raw[++i])
	{
		if (!ft_strncmp(raw[i], "|", 2) && (!raw[i + 1] || !ft_strncmp(raw[i
						+ 1], "|", 2)))
		{
			error_free(raw, "|");
			return (1);
		}
		else if ((!ft_strncmp(raw[i], ">", 1) || !ft_strncmp(raw[i], "<", 1))
			&& (!raw[i + 1] || ft_charincharset(raw[i + 1][0], "|<>")))
		{
			redirection_error(raw, i);
			return (1);
		}
	}
	return (0);
}
