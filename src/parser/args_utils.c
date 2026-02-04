/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:02:49 by ldesboui          #+#    #+#             */
/*   Updated: 2026/02/03 17:36:36 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	loop_count(t_cmd *cmd, int *i, int *count)
{
	if (cmd->raw[*i][0] != '"' && cmd->raw[*i][0] != '\''
		&& (!ft_strncmp(cmd->raw[*i], ">", 1)
		|| !ft_strncmp(cmd->raw[*i], "<", 1)))
	{
		(*i)++;
		if (cmd->raw[*i])
			(*i)++;
		return (0);
	}
	else if (!ft_strncmp(cmd->raw[*i], "|", 2))
		return (1);
	else
	{
		(*i)++;
		(*count)++;
		return (0);
	}
}

int	is_quote(char c, int quote)
{
	if (c == '\'' && quote == 0)
		return (1);
	if (c == '\'' && quote == 1)
		return (0);
	if (c == '"' && quote == 0)
		return (2);
	if (c == '"' && quote == 2)
		return (0);
	return (quote);
}

void	raw_to_args_loop(t_cmd *cmd, int status, char **env)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (cmd->raw[k])
	{
		if (cmd->raw[k][0] == '\0')
		{
			k++;
			continue ;
		}
		if (!ft_strncmp(cmd->raw[k], "|", 2))
		{
			link_cmd(cmd, k, env, status);
			break ;
		}
		else if (!ft_strncmp(cmd->raw[k], ">", 1) || !ft_strncmp(cmd->raw[k],
				"<", 1))
			k += (1 + (cmd->raw[k + 1] != NULL));
		else
			cmd->args[i++] = ft_strdup(cmd->raw[k++]);
	}
}
