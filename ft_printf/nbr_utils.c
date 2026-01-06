/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:51:10 by fgarnier          #+#    #+#             */
/*   Updated: 2025/10/17 01:16:26 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_base_unsigned(unsigned long n, char *base)
{
	int				count;
	unsigned long	base_len;

	count = 0;
	base_len = (unsigned long)ft_strlen(base);
	if (n >= base_len)
		count += ft_putnbr_base_unsigned(n / base_len, base);
	write(1, &base[n % base_len], 1);
	return (count + 1);
}

int	ft_putnbr_base(long n, char *base)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		count += 1;
		count += ft_putnbr_base_unsigned((unsigned long)(-(unsigned long)n),
				base);
		return (count);
	}
	return (count + ft_putnbr_base_unsigned((unsigned long)n, base));
}

int	ft_print_pointer(void *ptr)
{
	unsigned long	addr;
	int				count;

	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	addr = (unsigned long)ptr;
	count = 0;
	write(1, "0x", 2);
	count += 2;
	count += ft_putnbr_base_unsigned(addr, "0123456789abcdef");
	return (count);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	unsigned int	tmp;
	int				count;
	char			c;

	count = 0;
	tmp = n;
	if (tmp >= 10)
	{
		count += ft_putnbr_unsigned(tmp / 10);
	}
	c = tmp % 10 + '0';
	write(1, &c, 1);
	return (count + 1);
}
