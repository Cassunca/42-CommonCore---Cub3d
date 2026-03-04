/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:48:22 by amyrodri          #+#    #+#             */
/*   Updated: 2025/07/24 11:46:49 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		num[11];
	int			i;
	long int	nb;

	nb = (long int)n;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	i = 0;
	while (nb > 0)
	{
		num[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	while (--i >= 0)
		write(fd, &num[i], 1);
}
