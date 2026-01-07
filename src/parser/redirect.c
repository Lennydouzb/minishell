/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:48:28 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/07 15:21:21 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

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
	substr = ft_substr(str, i, k);
	if (!substr)
		return (-1);
	strtrimmed = ft_strtrim(substr, " <");
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
	fd = open(strtrimmed, O_WRONLY | O_CREAT);
	free (strtrimmed);
	return (fd);
}
