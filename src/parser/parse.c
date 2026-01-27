/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:32:34 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/27 19:22:10 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_cmd	*parsefunc(char *str)
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

void	parsefunc(t_cmd *cmd, char **env, int status)
{
	int	i;

	i = 0;
	if (!cmd->raw || !cmd->raw[0])
		return ;
	cmd->fdout = 1;
	while (cmd->raw[i])
	{
		if (ft_strncmp(cmd->raw[i], "<", 1) == 0)
		{
			if (cmd->fdin > 2)
				close(cmd->fdin);
			if (cmd->raw[i + 1])
				cmd->fdin = redirect(cmd->raw[i], cmd->raw[i + 1], env, status);
			if (cmd->fdin == -2)
			{
				// On peut marquer la commande comme "annulée"
				// et s'assurer que g_status passera à 130 dans le main
				return ;
			}
			i++;
		}
		else if (ft_strncmp(cmd->raw[i], ">", 1) == 0)
		{
			if (cmd->fdout > 2)
				close(cmd->fdout);
			if (cmd->raw[i + 1])
				cmd->fdout = redirect(cmd->raw[i], cmd->raw[i + 1], env,
						status);
			i++;
		}
		else if (ft_strncmp(cmd->raw[i], "|", 2) == 0)
			break ;
		++i;
	}
	ft_raw_to_args(cmd, env, status);
}

t_cmd	*parse(char *str, char **env, int status)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	ft_toraw(cmd, str);
	parsefunc(cmd, env, status);
	return (cmd);
}
