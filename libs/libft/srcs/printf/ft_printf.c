/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:47:56 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/24 17:05:17 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

static int	print_arg(va_list args, const char *format)
{
	if (*format == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (*format == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (*format == 'p')
		return (ft_putptr(va_arg(args, void *)));
	if (*format == 'd' || *format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (*format == 'u')
		return (ft_putuint(va_arg(args, unsigned int)));
	if (*format == 'x')
		return (ft_puthex(va_arg(args, unsigned int), "0123456789abcdef"));
	if (*format == 'X')
		return (ft_puthex(va_arg(args, unsigned int), "0123456789ABCDEF"));
	if (*format == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		j;
	va_list	args;

	va_start(args, format);
	i = 0;
	j = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			j += print_arg(args, &format[i + 1]);
			i += 2;
		}
		else
			j += ft_putchar(format[i++]);
	}
	va_end(args);
	return (j);
}
