/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:48:25 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/05 01:49:10 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_exec(char *path)
{
	struct stat	sb;

	if (access(path, X_OK) == 0)
	{
		stat(path, &sb);
		if (!S_ISDIR(sb.st_mode))
			return (1);
	}
	return (0);
}
