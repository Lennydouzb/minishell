/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 03:07:44 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 19:20:04 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_var(char *str, int i, int q)
{
	return (str[i] == '$' && q != 1 && str[i + 1] && (ft_isalnum(str[i + 1])
			|| str[i + 1] == '?' || str[i + 1] == '_'));
}

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
	q = 0;
	new = ft_strdup("");
	while (str[i])
	{
		q = is_quote(str[i], q);
		if (is_var(str, i, q))
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
	{
		final_args = add_arg(final_args, remove_quotes(split[j]));
		j++;
	}
	free(split);
	return (final_args);
}

void	expand_args(t_cmd *cmd, char **env, int status)
{
	char **final_args;
	char *expanded;
	int i;

	final_args = NULL;
	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_variables(cmd->args[i], env, status);
		if (!expanded[0])
			free(expanded);
		else
			final_args = process_arg(final_args, expanded);
		i++;
	}
	free(cmd->args);
	cmd->args = final_args;
}