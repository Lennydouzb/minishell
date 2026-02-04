/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 23:06:04 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/15 14:05:48 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddback(char *str1, char *str2)
{
	int		i;
	int		k;
	char	*new_str;

	if (!str1 || !str2)
		return (NULL);
	k = 0;
	new_str = ft_realloc(str1, ft_strlen(str1), ft_strlen(str1)
			+ ft_strlen(str2) + 1);
	if (!new_str)
		return (NULL);
	i = ft_strlen(new_str);
	while (str2[k])
	{
		new_str[i + k] = str2[k];
		++k;
	}
	new_str[i + k] = '\0';
	return (new_str);
}
