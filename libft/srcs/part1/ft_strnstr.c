/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:56:22 by amyrodri          #+#    #+#             */
/*   Updated: 2025/07/28 17:34:45 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = -1;
	while (big[++i] && i < len)
	{
		j = 0;
		while (little[j] && (i + j) < len && big[j + i] == little[j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
	}
	return (NULL);
}
