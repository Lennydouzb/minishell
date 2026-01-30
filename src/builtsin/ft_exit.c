/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:28:43 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 19:55:42 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

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

static void	exit_numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(2);
}

void	ft_exit(t_cmd *cmd)
{
	long long	val;

	// ft_putendl_fd("exit", 2); je sais pas dans les test faut le mettre
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return ;
	}
	else if (!cmd->args[1])
		exit(0);
	else if (!is_all_digit(cmd->args[1]))
		exit_numeric_error(cmd->args[1]);
	val = ft_atoll(cmd->args[1]);
	exit((val % 256 + 256) % 256);
}
