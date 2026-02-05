/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 03:07:44 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/05 01:31:29 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*expand_variables(char *str, char **env, int status, int q)
{
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	new = ft_strdup("");
	while (str[i])
	{
		q = is_quote(str[i], q);
		if (is_var(str, i, q))
			tmp = fetch_value(str, &i, env, status);
		else if (q == 0 && str[i] == '$' && (str[i + 1] == '\'' || str[i
					+ 1] == '"'))
		{
			++i;
			continue ;
		}
		else
			tmp = ft_substr(str, i++, 1);
		new = ft_straddback(new, tmp);
		free(tmp);
	}
	free(str);
	return (new);
}

static char	**add_arg(char **args, char *new_str)
{
	char	**new_args;
	int		len;
	int		i;

	len = 0;
	while (args && args[len])
		len++;
	new_args = ft_calloc(sizeof(char *), len + 2);
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = new_str;
	if (args)
		free(args);
	return (new_args);
}

static char	**process_arg(char **final_args, char *str)
{
	char	**split;
	int		j;

	if (!str || str[0] == '\0')
	{
		if (str)
			free(str);
		return (final_args);
	}
	if (str[0] == '"' || str[0] == '\'')
	{
		str = remove_quotes(str);
		final_args = add_arg(final_args, str);
		return (final_args);
	}
	split = ft_split_quote(str, ' ');
	free(str);
	if (!split)
		return (final_args);
	j = 0;
	while (split[j])
		final_args = add_arg(final_args, remove_quotes(split[j++]));
	free(split);
	return (final_args);
}

void	expand_args(t_cmd *cmd, char **env, int status)
{
	char	**final_args;
	char	*expanded;
	int		i;

	final_args = NULL;
	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_variables(cmd->args[i], env, status, 0);
		final_args = process_arg(final_args, expanded);
		i++;
	}
	free(cmd->args);
	if (!final_args)
		final_args = ft_calloc(sizeof(char *), 1);
	cmd->args = final_args;
}
