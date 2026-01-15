/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:36:35 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/15 14:37:15 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int i;
	int n_option;

	i = 1;
	n_option = 0;
	if (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 3) == 0)
	{
		n_option = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], cmd->fdout);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", cmd->fdout);
		i++;
	}
	if (n_option == 0)
		ft_putstr_fd("\n", cmd->fdout);
}