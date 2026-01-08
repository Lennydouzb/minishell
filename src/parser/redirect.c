/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:48:28 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/08 21:00:48 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include <fcntl.h>

int	redirectin(char *str, int i)
{
	char	*substr;
	char	*strtrimmed;
	int		k;
	int		fd;
	int		found;

	k = 1;
	found = 0;
	while (str[i + k] && found == 0)
	{
		if (str[i + k] == '>' || str[i + k] == '<' || str[i + k] == '|')
			found = 1;
		++k;
	}
	if (found == 0)
		return (0);
	substr = ft_substr(str, i, k);
	if (!substr)
		return (-1);
	strtrimmed = ft_strtrim(substr, " <>|");
	free(substr);
	if (!strtrimmed)
		return (-1);
	fd = open(strtrimmed, O_RDONLY);
	free (strtrimmed);
	return (fd);
}

int	redirectout(char *str, int i)
{
	char	*substr;
	char	*strtrimmed;
	int		k;
	int		fd;
	int		found;

	k = 1;
	found = 0;
	while (str[i + k] && found == 0)
	{
		if (str[i + k] == '>' || str[i + k] == '<' || str[i + k] == '|')
			found = 1;
		++k;
	}
	substr = ft_substr(str, i, k);
	if (!substr)
		return (-1);
	strtrimmed = ft_strtrim(substr, " >");
	free(substr);
	if (!strtrimmed)
		return (-1);
	fd = open(strtrimmed, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free (strtrimmed);
	return (fd);
}
