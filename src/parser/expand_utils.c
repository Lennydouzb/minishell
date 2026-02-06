/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:04:24 by ldesboui          #+#    #+#             */
/*   Updated: 2026/02/05 11:34:59 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	is_var(char *str, int i, int q)
{
	return (str[i] == '$' && q != 1 && str[i + 1] && (ft_isalnum(str[i + 1])
			|| str[i + 1] == '?' || str[i + 1] == '_'));
}

char	*extract_var_name(char *str, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

void	mask_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '\'')
			str[i] = 1;
		else if (str[i] == '"')
			str[i] = 2;
		i++;
	}
}

void	unmask_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == 1)
			str[i] = '\'';
		else if (str[i] == 2)
			str[i] = '"';
		i++;
	}
}
