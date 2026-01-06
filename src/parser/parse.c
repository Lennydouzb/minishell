/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:32:34 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/06 19:14:28 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parsefunc(char *str)
{
	t_cmd	*cmd;
	char	**strs;
	int		i;

	i = 0;
	strs = ft_split(str, ' ');
	if (!strs)
	{
		perror("Error");
		return (NULL);
	}
	while (strs[i])
	{
		cmd->args[i] = strs[i];
		++i;
	}
	cmd->args[i] = "\0";
	return (cmd);
}

t_cmd	*parse(char *str)
{
	t_cmd	*cmd;

	cmd = parsefunc(str);
	if (!cmd)
		return (NULL);

}
