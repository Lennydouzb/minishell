/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:32:34 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/11 09:21:07 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//t_cmd	*parsefunc(char *str)
//{
//	int		i;
//	t_cmd	*cmd;
//
//	i = 0;
//	cmd = ft_calloc(sizeof(t_cmd), 1);
//	if (!cmd)
//		return (NULL);
//	cmd->fdout = 1;
//	while (str[i])
//	{
//		if (str[i] == '<' && str[i + 1] != '<')
//			cmd->fdin = redirectin(str, i);
//		if (str[i] == '>' && str[i + 1] != '>')
//			cmd->fdout = redirectout(str, i);
//		++i;
//	}
//	ft_toargs(cmd, str, ft_strlen(str));
//	return (cmd);
//}

void	parsefunc(t_cmd	*cmd)
{
	int		i;

	i = 0;
	if (!cmd->raw)
		return ;
	cmd->fdout = 1;
	while (cmd->raw[i])
	{
		if (ft_charsetinstr(cmd->raw[i], "<") && ft_charsetinstr(cmd->raw[i + 1], "<") == 0)
			cmd->fdin = redirectin(cmd->raw[i + 1]);
		if (ft_charsetinstr(cmd->raw[i], ">") && ft_charsetinstr(cmd->raw[i + 1], ">") == 0)
			cmd->fdout = redirectout(cmd->raw[i + 1]);
		if (ft_charsetinstr(cmd->raw[i], "|"))
				break ;
		++i;
	}
	ft_raw_to_args(cmd);
}

t_cmd	*parse(char *str)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	ft_toraw(cmd, str);
	parsefunc(cmd);
	return (cmd);
}
