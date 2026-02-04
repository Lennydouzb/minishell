/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 02:44:49 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/03 20:37:23 by ldesboui         ###   ########.fr       */
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
		stop = loop_count(cmd, &i, &count);
	}
	return (count);
}

void	link_cmd(t_cmd *cmd, int k, char **env, int status)
{
	t_cmd	*nextcmd;
	int		pfd[2];

	if (pipe(pfd) != 0)
		return ;
	if (cmd->fdout == 1)
		cmd->fdout = pfd[1];
	else
		close(pfd[1]);
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
	raw_to_args_loop(cmd, status, env);
	expand_args(cmd, env, status);
	if (cmd->args && cmd->args[0])
		cmd->path = get_env_path(cmd, env, NULL);
}

void	ft_toraw(t_cmd *cmd, char *str)
{
	char	*substr;

	substr = ft_substr(str, 0, ft_strlen(str));
	if (!str)
		return ;
	substr = putspace(substr);
	cmd->raw = ft_split_quote(substr, ' ');
	free(substr);
}
