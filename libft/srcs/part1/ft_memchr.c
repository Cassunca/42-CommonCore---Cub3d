/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:47:56 by amyrodri          #+#    #+#             */
/*   Updated: 2025/07/21 16:14:49 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t n)
{
	size_t				i;
	const unsigned char	*p;

	p = (const unsigned char *)ptr;
	i = -1;
	while (++i < n)
		if (p[i] == (unsigned char)c)
			return ((void *)&p[i]);
	return (NULL);
}
