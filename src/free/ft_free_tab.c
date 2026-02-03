/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:24:58 by fgarnier          #+#    #+#             */
/*   Updated: 2026/02/01 19:02:26 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tab(char **tab_)
{
	int	i;

	if (!tab_)
		return ;
	i = 0;
	while (tab_[i])
		free(tab_[i++]);
	free(tab_);
}
