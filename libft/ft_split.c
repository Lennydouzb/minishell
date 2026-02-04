/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:45:41 by fgarnier          #+#    #+#             */
/*   Updated: 2025/10/15 09:14:38 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_wordlen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_worddup(char const *src, char c)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (ft_wordlen(src, c) + 1));
	if (!dest)
		return (NULL);
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] != c)
			&& (i == 0 || str[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		count;
	int		i;

	i = 0;
	count = 0;
	res = malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if ((s[i] != c) && (i == 0 || s[i - 1] == c))
		{
			res[count] = ft_worddup(&s[i], c);
			if (!res[count])
			{
				free_split(res, count);
				return (NULL);
			}
			count++;
		}
		i++;
	}
	res[count] = NULL;
	return (res);
}
