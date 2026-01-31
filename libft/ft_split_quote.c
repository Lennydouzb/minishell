/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:45:41 by fgarnier          #+#    #+#             */
/*   Updated: 2026/01/31 03:26:48 by fgarnier         ###   ########.fr       */
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
		if (in_word == 0 && (!is_sep(str[i], c) || quote != 0))
		{
			in_word = 1;
			count++;
		}
		else if (in_word == 1 && is_sep(str[i], c) && quote == 0)
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
	while (src[len] && (!is_sep(src[len], c) || quote != 0))
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

static int	fill_res(char **res, char const *s, char c)
{
	int	i;
	int	cnt;
	int	q;
	int	w;

	i = 0;
	cnt = 0;
	q = 0;
	w = 0;
	while (s[i])
	{
		if (w == 0 && (!is_sep(s[i], c) || q != 0))
		{
			res[cnt] = ft_worddup(&s[i], c);
			if (!res[cnt++])
				return (cnt - 1);
			w = 1;
		}
		else if (w == 1 && is_sep(s[i], c) && q == 0)
			w = 0;
		q = update_quote(s[i++], q);
	}
	res[cnt] = NULL;
	return (-1);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**res;
	int		err;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (NULL);
	err = fill_res(res, s, c);
	if (err >= 0)
	{
		free_split(res, err);
		return (NULL);
	}
	return (res);
}
