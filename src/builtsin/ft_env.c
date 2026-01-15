/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:18:36 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/15 15:21:15 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_cmd *cmd, char **env)
{
	int i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], cmd->fdout);
			ft_putstr_fd("\n", cmd->fdout);
		}
		i++;
	}
}