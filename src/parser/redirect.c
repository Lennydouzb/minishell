/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:48:28 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/11 08:43:25 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include <fcntl.h>

int	redirectin(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	return (fd);
}

int	redirectout(char *str)
{
	int		fd;

	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}
