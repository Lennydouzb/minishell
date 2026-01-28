/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 02:44:49 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/28 03:13:46 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count(t_cmd *cmd)
{
	int	i;
	int	count;
	int	stop;

	stop = 0;
	count = 0;
	i = 0;
	while (cmd->raw[i] && stop == 0)
	{
		if (!ft_strncmp(cmd->raw[i], ">", 1) || !ft_strncmp(cmd->raw[i], "<",
				1))
		{
			i++;
			if (cmd->raw[i])
				i++;
		}
		else if (!ft_strncmp(cmd->raw[i], "|", 2))
			stop = 1;
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

static void	link_cmd(t_cmd *cmd, int k, char **env, int status)
{
	t_cmd	*nextcmd;
	int		pfd[2];

	if (pipe(pfd) != 0)
		return ;
	if (cmd->fdout == 1)
		cmd->fdout = pfd[1];
	nextcmd = ft_calloc(sizeof(t_cmd), 1);
	if (!nextcmd)
		return ;
	nextcmd->raw = &(cmd->raw[k + 1]);
	nextcmd->fdin = pfd[0];
	parsefunc(nextcmd, env, status);
	cmd->next = nextcmd;
}

void	ft_raw_to_args(t_cmd *cmd, char **env, int status)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	cmd->args = ft_calloc(sizeof(char *), count(cmd) + 1);
	if (!(cmd->args))
		return ;
	while (cmd->raw[k])
	{
		if (!ft_strncmp(cmd->raw[k], "|", 2))
		{
			link_cmd(cmd, k, env, status);
			break ;
		}
		else if (!ft_strncmp(cmd->raw[k], ">", 1) || !ft_strncmp(cmd->raw[k],
				"<", 1))
			k += (1 + (cmd->raw[k + 1] != NULL));
		else
			cmd->args[i++] = cmd->raw[k++];
	}
	expand_args(cmd, env, status);
	cmd->path = get_env_path(cmd, env);
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

void	ft_toraw(t_cmd *cmd, char *str)
{
	char	*substr;

	substr = ft_substr(str, 0, ft_strlen(str));
	if (!str)
		return ;
	substr = putspace(substr);
	cmd->raw = ft_split_quote(substr, ' ');
}
