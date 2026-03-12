/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:07:48 by amyrodri          #+#    #+#             */
/*   Updated: 2025/07/23 13:32:25 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennum(long nb)
{
	int	len;

	len = (nb < 0);
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	long			nb;
	unsigned int	cd;

	nb = (long)n;
	if (nb == 0)
		return (ft_strdup("0"));
	cd = ft_lennum(nb);
	str = ft_calloc(cd + 1, 1);
	if (!str)
		return (NULL);
	str[cd] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--cd] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
