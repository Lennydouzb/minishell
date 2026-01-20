/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:00:54 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/19 15:27:10 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_cmd *cmd, char ***env)
{
	int		i;
	int		j;
	int		len;
	char	**old_env;

	j = 1;
	while (cmd->args[j])
	{
		i = 0;
		old_env = *env;
		len = ft_strlen(cmd->args[j]);
		while (old_env[i])
		{
			if (ft_strncmp(old_env[i], cmd->args[j], len) == 0
				&& old_env[i][len] == '=')
			{
				free(old_env[i]);
				while (old_env[i])
				{
					old_env[i] = old_env[i + 1];
					i++;
				}
				break ;
			}
			i++;
		}
		j++;
	}
	return (0);
}
