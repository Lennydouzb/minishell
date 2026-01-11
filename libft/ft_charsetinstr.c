/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charsetinstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:34:15 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/07 19:38:35 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_charsetinstr(const char *str, const char *set)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		k = 0;
		while (set[k])
		{
			if (str[i] == set[k])
				return (1);
			++k;
		}
		++i;
	}
	return (0);
}
