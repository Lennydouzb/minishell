/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarnier <fgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:27:43 by fgarnier          #+#    #+#             */
/*   Updated: 2025/10/17 01:20:18 by fgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int n, char specifier)
{
	if (specifier == 'x')
		return (ft_putnbr_base((long)(unsigned int)n, "0123456789abcdef"));
	else
		return (ft_putnbr_base((long)(unsigned int)n, "0123456789ABCDEF"));
}

int	print_format(char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (specifier == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_base((long)va_arg(args, int), "0123456789"));
	if (specifier == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	if (specifier == 'x' || specifier == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), specifier));
	if (specifier == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	if (specifier == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		total;

	if (!s)
		return (0);
	i = 0;
	total = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (!s[i])
				break ;
			total += print_format(s[i], args) - 1;
		}
		else
			write(1, &s[i], 1);
		total++;
		i++;
	}
	va_end(args);
	return (total);
}
