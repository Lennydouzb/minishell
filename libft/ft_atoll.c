/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:04:55 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/19 17:13:11 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

__int128_t	ft_atoll(const char *str)
{
	int			i;
	int			signe;
	__int128_t	res;

	signe = 1;
	i = 0;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * signe);
}
