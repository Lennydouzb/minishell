/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:04:24 by ldesboui          #+#    #+#             */
/*   Updated: 2026/02/03 16:05:26 by ldesboui         ###   ########.fr       */
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
