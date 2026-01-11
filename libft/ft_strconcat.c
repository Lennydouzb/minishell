/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:37:12 by ldesboui          #+#    #+#             */
/*   Updated: 2026/01/07 11:41:32 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strconcat(const char *str1, char *str2)
{
	int		i;
	int		k;
	char	*concat;

	i = 0;
	k = 0;
	concat = ft_calloc(ft_strlen(str1), ft_strlen(str2));
	if (!concat)
		return (NULL);
	while (str1[i])
	{
		concat[i] = str1[i];
		++i;
	}
	while (str2[k])
	{
		concat[i + k] = str2[k];
		++k;
	}
	return (concat);
}
