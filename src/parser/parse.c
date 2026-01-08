/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:32:34 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/08 22:45:14 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parsefunc(char *str)
{
	int		i;
	t_cmd	*cmd;
	int		foundone;

	foundone = -1;
	i = 0;
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->fdout = 1;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<')
			cmd->fdin = redirectin(str, i);
		if (str[i] == '>' && str[i + 1] != '>')
			cmd->fdout = redirectout(str, i);
		++i;
	}
	ft_toargs(cmd, str, ft_strlen(str));
	return (cmd);
}

t_cmd	*parse(char *str)
{
	t_cmd	*cmd;

	cmd = parsefunc(str);
	if (!cmd)
		return (NULL);
	return (cmd);
}
