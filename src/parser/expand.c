/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 03:07:44 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/28 03:22:37 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_var_name(char *str, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*fetch_value(char *str, int *i, char **env, int status)
{
	char	*key;
	char	*val;

	if (str[*i + 1] == '?')
	{
		*i += 2;
		return (ft_itoa(status));
	}
	key = extract_var_name(str, i);
	val = ft_strdup(get_env_val(key, env));
	free(key);
	return (val);
}

char	*expand_variables(char *str, char **env, int status)
{
	int		i;
	int		q;
	char	*new;
	char	*tmp;

	i = 0;
	new = ft_strdup("");
	while (str[i])
	{
		q = is_quote(str[i], q);
		if (str[i] == '$' && q != 1 && str[i + 1] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '?' || str[i + 1] == '_'))
		{
			tmp = fetch_value(str, &i, env, status);
			new = ft_straddback(new, tmp);
		}
		else
		{
			tmp = ft_substr(str, i++, 1);
			new = ft_straddback(new, tmp);
			free(tmp);
		}
	}
	free(str);
	return (new);
}

void	expand_args(t_cmd *cmd, char **env, int status)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		cmd->args[i] = expand_variables(cmd->args[i], env, status);
		cmd->args[i] = remove_quotes(cmd->args[i]);
		i++;
	}
}
