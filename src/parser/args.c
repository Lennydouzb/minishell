/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:28:51 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/07 20:01:42 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static int	count(t_cmd *cmd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (cmd->raw[i])
	{
		if (ft_charsetinstr(cmd->raw[i], "><") == 0)
			++count;
		++i;
	}
	return (count);
}

static void	ft_raw_to_args(t_cmd *cmd)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	cmd->args = ft_calloc(sizeof(char *), count(cmd));
	if (!(cmd->args))
		return ;
	while (cmd->raw[k])
	{
		if (ft_charsetinstr(cmd->raw[k], "><") == 0)
		{
			cmd->args[i] = cmd->raw[k];
			++i;
			++k;
		}
		else
			++k;
	}
}

void	ft_toargs(t_cmd *cmd, char *str, int i)
{
	char	*substr;

	substr = ft_substr(str, 0, i);
	if (!str)
		return ;
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
