/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:45:41 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/15 01:45:09 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	update_quote(char c, int quote)
{
	if (c == '\'' && quote == 0)
		return (1);
	if (c == '"' && quote == 0)
		return (2);
	if (c == '\'' && quote == 1)
		return (0);
	if (c == '"' && quote == 2)
		return (0);
	return (quote);
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;
	int	quote;
	int	in_word;

	i = 0;
	count = 0;
	quote = 0;
	in_word = 0;
	while (str[i])
	{
		if (in_word == 0 && (str[i] != c || quote != 0))
		{
			in_word = 1;
			count++;
		}
		else if (in_word == 1 && str[i] == c && quote == 0)
			in_word = 0;
		quote = update_quote(str[i], quote);
		i++;
	}
	return (count);
}

static char	*ft_worddup(char const *src, char c)
{
	int		len;
	int		quote;
	char	*dest;

	len = 0;
	quote = 0;
	while (src[len] && (src[len] != c || quote != 0))
	{
		quote = update_quote(src[len], quote);
		len++;
	}
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, src, len);
	dest[len] = '\0';
	return (dest);
}

static void	*free_split(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split_quote(char const *s, char c)
{
	char **res;
	int i;
	int count;
	int quote;
	int in_word;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	count = 0;
	quote = 0;
	in_word = 0;
	while (s[i])
	{
		if (in_word == 0 && (s[i] != c || quote != 0))
		{
			res[count] = ft_worddup(&s[i], c);
			if (!res[count++])
				return (free_split(res, count - 1));
			in_word = 1;
		}
		else if (in_word == 1 && s[i] == c && quote == 0)
			in_word = 0;
		quote = update_quote(s[i], quote);
		i++;
	}
	res[count] = NULL;
	return (res);
}
