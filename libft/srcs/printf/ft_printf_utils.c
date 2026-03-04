/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:59:54 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/24 17:05:13 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(const char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6));
	i = -1;
	while (s[++i])
		write(1, &s[i], 1);
	return (i);
}

int	ft_putptr(void *p)
{
	if (!p)
		return (write(1, "(nil)", 5));
	return (ft_putstr("0x") + ft_puthex((unsigned long)p, "0123456789abcdef"));
}

int	ft_putnbr(int n)
{
	long int	nb;
	int			i;

	i = 0;
	nb = (long int)n;
	if (nb < 0)
	{
		i += write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		i += ft_putnbr(nb / 10);
	i += write(1, &"0123456789"[nb % 10], 1);
	return (i);
}

int	ft_putuint(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr >= 10)
		i += ft_putuint(nbr / 10);
	i += write(1, &"0123456789"[nbr % 10], 1);
	return (i);
}

int	ft_puthex(unsigned long n, char *base)
{
	int		i;

	i = 0;
	if (n >= 16)
		i += ft_puthex(n / 16, base);
	i += write(1, &base[n % 16], 1);
	return (i);
}
