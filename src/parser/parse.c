/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:32:34 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/07 19:40:25 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



t_cmd	*parsefunc(char *str)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = ft_calloc(sizeof(t_cmd), 1);
	while (str[i])
	{
		if (str[i] == '<')
		{
			ft_toargs(cmd, str, i);
			if (str[i + 1] == '<')
				printf("\n----heredoc mode-----\n");
			else
				cmd->fdin = redirectin(str, i);
		}
		if (str[i] == '>')
		{
			ft_toargs(cmd, str, i);
			if (str[i + 1] == '>')
				printf("\n----append mode-----\n");
			else
				cmd->fdout = redirectout(str, i);
		}
		if (str[i] == '|')
		{
			ft_toargs(cmd, str, i);
		}
		if (str[i] == 39)
		{
			//@todo a corriger, deja '
			while (str[i] != 39 && str[i])
				++i;
			if (!str[i])
				--i;
		}
		if (str[i] == '"')
		{
			while (str[i] != '"' && str[i])
				++i;
			if (!str[i])
				--i;
		}
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
