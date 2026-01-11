/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:28:51 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/11 07:08:52 by ldesboui         ###   ########.fr       */
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
		if (ft_charsetinstr(cmd->raw[i], "><") == 1)
		{
			++i;
			if (cmd->raw[i])
				++i;
		}
		else if (ft_charsetinstr(cmd->raw[i], "|"))
			stop = 1;
		else
		{
			++i;
			++count;
		}
	}
	return (count);
}

static void	link_cmd(t_cmd *cmd, int k)
{
	t_cmd	*nextcmd;
	int		pfd[2];
	int		valid;

	valid = pipe(pfd);
	if (valid != 0)
		return ;
	cmd->fdout = pfd[1];
	nextcmd = ft_calloc(sizeof(t_cmd), 1);
	nextcmd->raw = &(cmd->raw[k + 1]);
	nextcmd->fdin = pfd[0];
	ft_raw_to_args(nextcmd);
	if (!nextcmd)
		return ;
	cmd->next = nextcmd;
}

void	ft_raw_to_args(t_cmd *cmd)
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
		if (ft_charsetinstr(cmd->raw[k], "|") == 1)
		{
			link_cmd(cmd, k);
			return ;
		}
		else if (ft_charsetinstr(cmd->raw[k], "><") == 1)
		{
			++k;
			if (cmd->raw[k])
			{
				++k;
			}
		}
		else
			cmd->args[i++] = cmd->raw[k++];
	}
}

static int	countspace(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_charincharset(str[i], "<>|") == 1)
			count += 2;
		++count;
		++i;
	}
	return (count);
}
static char	*putspace(char *str)
{
	int		i;
	char	*spaced;
	int		k;

	spaced = ft_calloc(sizeof(char), countspace(str) + 1);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			spaced[k++] = ' ';
			spaced[k++] = str[i++];
			spaced[k++] = ' ';
		}
		else
		{
			spaced[k++] = str[i++];
		}
	}
	free(str);
	return (spaced);
}

void	ft_toargs(t_cmd *cmd, char *str, int i)
{
	char	*substr;

	substr = ft_substr(str, 0, i);
	if (!str)
		return ;
	substr = putspace(substr);
	cmd->raw = ft_split(substr, ' ');
	if (!(cmd->raw))
	{
		free(str);
		return ;
	}
	ft_raw_to_args(cmd);
	cmd->path = ft_strconcat("/bin/", cmd->args[0]);
	return ;
}
