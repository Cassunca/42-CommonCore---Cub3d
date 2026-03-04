/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:05:18 by amyrodri          #+#    #+#             */
/*   Updated: 2025/07/24 16:45:49 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ar;

	if (!nmemb || !size)
		return (malloc(1));
	if (nmemb && size > (size_t)-1 / nmemb)
		return (NULL);
	ar = malloc(nmemb * size);
	if (!ar)
		return (NULL);
	ft_bzero(ar, nmemb * size);
	return (ar);
}
