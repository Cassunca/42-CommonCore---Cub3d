/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:22:29 by amyrodri          #+#    #+#             */
/*   Updated: 2025/07/24 14:04:40 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	if (!dest && !src && n > 0)
		return (NULL);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	i = -1;
	if (d < s)
	{
		while (++i < n)
			d[i] = s[i];
	}
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}
