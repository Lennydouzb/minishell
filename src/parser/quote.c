/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 01:36:56 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/15 01:36:57 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_clean_len(char *str)
{
	int	i;
	int	len;
	int	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '"' && quote == 0)
			quote = 2;
		else if (str[i] == '\'' && quote == 1)
			quote = 0;
		else if (str[i] == '"' && quote == 2)
			quote = 0;
		else
			len++;
		i++;
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	char *new;
	int i;
	int j;
	int quote;

	new = malloc(sizeof(char) * (get_clean_len(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '"' && quote == 0)
			quote = 2;
		else if ((str[i] == '\'' && quote == 1) || (str[i] == '"'
				&& quote == 2))
			quote = 0;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}