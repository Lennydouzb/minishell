/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:45:33 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 18:59:32 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

int	check_syntax_error(char **raw)
{
	int	i;

	i = -1;
	if (raw[0] && !ft_strncmp(raw[0], "|", 2))
	{
		syntax_error("|");
		return (1);
	}
	while (raw[++i])
	{
		if (!ft_strncmp(raw[i], "|", 2) && (!raw[i + 1] || !ft_strncmp(raw[i
						+ 1], "|", 2)))
		{
			syntax_error("|");
			return (1);
		}
		else if ((!ft_strncmp(raw[i], ">", 1) || !ft_strncmp(raw[i], "<", 1))
			&& (!raw[i + 1] || ft_charincharset(raw[i + 1][0], "|<>")))
		{
			syntax_error("newline");
			return (1);
		}
	}
	return (0);
}
