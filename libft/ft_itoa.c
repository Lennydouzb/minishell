/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:35:48 by fgarnier          #+#    #+#             */
/*   Updated: 2025/10/15 10:33:38 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	intlen(long n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*res;
	int		len;
	int		is_neg;

	nb = n;
	is_neg = (nb < 0);
	if (nb < 0)
		nb = -nb;
	len = intlen(nb) + is_neg;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len > is_neg)
	{
		res[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	if (is_neg)
		res[0] = '-';
	return (res);
}
