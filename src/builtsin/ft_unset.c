/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:00:54 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/28 03:24:02 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_one_var(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			while (env[i])
			{
				env[i] = env[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

int	ft_unset(t_cmd *cmd, char ***env)
{
	int	j;

	j = 1;
	while (cmd->args[j])
	{
		remove_one_var(*env, cmd->args[j]);
		j++;
	}
	return (0);
}
