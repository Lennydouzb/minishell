/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:01:34 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/19 15:16:41 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Vérifie si le nom de variable est valide (lettres, chiffres, _)
static int	is_valid_id(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	add_to_env(char *new_var, char ***env)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
}

static void	remove_from_env(char *new_var, char ***env)
{
	int		i;
	int		len;
	char	**old_env;

	i = 0;
	old_env = *env;
	len = 0;
	while (new_var[len] != '=' && new_var[len])
		len++;
	while (old_env[i])
	{
		if (ft_strncmp(old_env[i], new_var, len) == 0 && old_env[i][len] == '=')
		{
			free(old_env[i]);
			while (old_env[i])
			{
				old_env[i] = old_env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

int	ft_export(t_cmd *cmd, char ***env)
{
	int	k;

	k = 1;
	if (!cmd->args[k])
		return (ft_env(cmd, *env));
	while (cmd->args[k])
	{
		if (!is_valid_id(cmd->args[k]))
		{
			ft_putstr_fd("export: not a valid identifier\n", 2);
			k++;
			return (1);
		}
		if (ft_strchr(cmd->args[k], '='))
		{
			remove_from_env(cmd->args[k], env);
			add_to_env(cmd->args[k], env);
		}
		k++;
	}
	return (0);
}
