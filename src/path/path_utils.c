/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:22:16 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/05 01:30:46 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*create_env_string(char *key, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

static int	add_new_var(char ***env, char *new_str)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i + 2);
	if (!new_env)
		return (1);
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = new_str;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	set_env_var(char ***env, char *key, char *value)
{
	int		i;
	int		key_len;
	char	*new_str;

	new_str = create_env_string(key, value);
	if (!new_str)
		return (1);
	key_len = ft_strlen(key);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], key, key_len) == 0
			&& (*env)[i][key_len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_str;
			return (0);
		}
		i++;
	}
	return (add_new_var(env, new_str));
}
