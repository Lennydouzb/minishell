/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 02:42:47 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/28 03:07:21 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	countspace(char *str)
{
	int	i;
	int	count;
	int	quote;

	i = -1;
	count = 0;
	quote = 0;
	while (str[++i])
	{
		quote = is_quote(str[i], quote);
		if (ft_charincharset(str[i], "<>|") && quote == 0)
		{
			count += 2;
			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
						+ 1] == '<'))
			{
				i++;
				count++;
			}
		}
		count++;
	}
	return (count);
}

static void	fill_spaced_str(char *str, char *spaced)
{
	int	i;
	int	k;
	int	quote;

	i = 0;
	k = 0;
	quote = 0;
	while (str[i])
	{
		quote = is_quote(str[i], quote);
		if (ft_charincharset(str[i], "<>|") && quote == 0)
		{
			spaced[k++] = ' ';
			spaced[k++] = str[i];
			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
						+ 1] == '<'))
				spaced[k++] = str[++i];
			spaced[k++] = ' ';
			i++;
		}
		else
			spaced[k++] = str[i++];
	}
}

char	*putspace(char *str)
{
	char	*spaced;

	spaced = ft_calloc(sizeof(char), countspace(str) + 1);
	if (!spaced)
		return (NULL);
	fill_spaced_str(str, spaced);
	free(str);
	return (spaced);
}
