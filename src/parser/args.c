/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:28:51 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/15 01:55:04 by fgarnier         ###   ########.fr       */
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
		if (ft_strncmp(cmd->raw[i], ">", 2) == 0 || ft_strncmp(cmd->raw[i], "<",
				2) == 0)
		{
			++i;
			if (cmd->raw[i])
				++i;
		}
		else if (ft_strncmp(cmd->raw[i], "|", 2) == 0)
			stop = 1;
		else
		{
			++i;
			++count;
		}
	}
	return (count);
}

static void	link_cmd(t_cmd *cmd, int k, char **env)
{
	t_cmd	*nextcmd;
	int		pfd[2];
	int		valid;

	valid = pipe(pfd);
	if (valid != 0)
		return ;
	if (cmd->fdout == 1)
		cmd->fdout = pfd[1];
	nextcmd = ft_calloc(sizeof(t_cmd), 1);
	if (!nextcmd)
		return ;
	nextcmd->raw = &(cmd->raw[k + 1]);
	nextcmd->fdin = pfd[0];
	parsefunc(nextcmd, env);
	cmd->next = nextcmd;
}

void	ft_raw_to_args(t_cmd *cmd, char **env)
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
		if (ft_strncmp(cmd->raw[i], "|", 2) == 0)
		{
			link_cmd(cmd, k, env);
			break ;
		}
		else if (ft_strncmp(cmd->raw[i], ">", 2) == 0 || ft_strncmp(cmd->raw[i],
				"<", 2) == 0)
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
	i = 0;
	while (cmd->args[i])
	{
		cmd->args[i] = remove_quotes(cmd->args[i]);
		i++;
	}
	cmd->path = get_PATH(cmd, env);
}

static int	countspace(char *str)
{
	int	i;
	int	count;
	int	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '\'' && quote == 1)
			quote = 0;
		else if (str[i] == '"' && quote == 0)
			quote = 2;
		else if (str[i] == '"' && quote == 2)
			quote = 0;
		if (ft_charincharset(str[i], "<>|") == 1 && quote == 0)
			count += 2;
		count++;
		i++;
	}
	return (count);
}

static char	*putspace(char *str)
{
	int		i;
	int		k;
	char	*spaced;
	int		quote;

	i = 0;
	k = 0;
	quote = 0; // 0: none, 1: ', 2: "
	spaced = ft_calloc(sizeof(char), countspace(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '\'' && quote == 1)
			quote = 0;
		else if (str[i] == '"' && quote == 0)
			quote = 2;
		else if (str[i] == '"' && quote == 2)
			quote = 0;
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>') && quote == 0)
		{
			spaced[k++] = ' ';
			spaced[k++] = str[i++];
			spaced[k++] = ' ';
		}
		else
			spaced[k++] = str[i++];
	}
	free(str);
	return (spaced);
}

// void	ft_toargs(t_cmd *cmd, char *str, int i)
//{
//	char	*substr;
//
//	substr = ft_substr(str, 0, i);
//	if (!str)
//		return ;
//	substr = putspace(substr);
//	cmd->raw = ft_split(substr, ' ');
//	if (!(cmd->raw))
//	{
//		free(str);
//		return ;
//	}
//	ft_raw_to_args(cmd);
//	return ;
//}

void	ft_toraw(t_cmd *cmd, char *str)
{
	char	*substr;

	substr = ft_substr(str, 0, ft_strlen(str));
	if (!str)
		return ;
	substr = putspace(substr);
	cmd->raw = ft_split_quote(substr, ' ');
}
