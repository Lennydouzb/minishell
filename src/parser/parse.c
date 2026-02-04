/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:32:34 by ldesboui          #+#    #+#             */
/*   Updated: 2026/02/02 20:18:01 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_redirection(t_cmd *cmd, int i, char **env, int status)
{
	if (cmd->fdin == -1 || cmd->fdout == -1)
		return (0);
	if (ft_strncmp(cmd->raw[i], "<", 1) == 0)
	{
		if (cmd->fdin > 2)
			close(cmd->fdin);
		if (cmd->raw[i + 1])
			cmd->fdin = redirect(cmd->raw[i], cmd->raw[i + 1], env, status);
		if (cmd->fdin == -2)
			return (-2);
		if (cmd->fdin == -1)
			return (-1);
		return (1);
	}
	else if (ft_strncmp(cmd->raw[i], ">", 1) == 0)
	{
		if (cmd->fdout > 2)
			close(cmd->fdout);
		if (cmd->raw[i + 1])
			cmd->fdout = redirect(cmd->raw[i], cmd->raw[i + 1], env, status);
		if (cmd->fdout == -1)
			return (-1);
		return (1);
	}
	return (0);
}

void	parsefunc(t_cmd *cmd, char **env, int status)
{
	int	i;
	int	ret;

	i = 0;
	if (!cmd->raw || !cmd->raw[0])
		return ;
	cmd->fdout = 1;
	while (cmd->raw[i])
	{
		if (ft_strncmp(cmd->raw[i], "|", 2) == 0)
			break ;
		if (cmd->raw[i][0] == '\'' || cmd->raw[i][0] == '"')
			ret = 0;
		else
			ret = handle_redirection(cmd, i, env, status);
		if (ret == -2)
			return ;
		if (ret == -1)
			cmd->fdin = -1;
		if (ret == 1 || ret == -1)
			i++;
		i++;
	}
	ft_raw_to_args(cmd, env, status);
}

t_cmd	*parse(char *str, char **env, int status)
{
	t_cmd	*cmd;
	int		k;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	ft_toraw(cmd, str);
	if (check_syntax_error(cmd->raw))
	{
		if (cmd->raw)
			free_split(cmd->raw, 0);
		else
		{
			k = 0;
			while (cmd->raw[k])
				free(cmd->raw[k++]);
			free(cmd->raw);
		}
		free(cmd);
		return (NULL);
	}
	parsefunc(cmd, env, status);
	return (cmd);
}
