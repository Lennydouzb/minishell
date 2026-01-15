/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:28:43 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/15 15:29:15 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	int	exit_status;

	ft_putendl_fd("exit", 2);
	if (cmd->args[1])
	{
		if (!is_all_digit(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			// Nettoyage mémoire
			exit(2);
		}
		if (cmd->args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return ;
		}
		exit_status = ft_atoi(cmd->args[1]);
		// Nettoyage mémoire
		exit(exit_status);
	}
	// Nettoyage mémoire
	exit(0);
}
