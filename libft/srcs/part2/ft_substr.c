/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:46:18 by amyrodri          #+#    #+#             */
/*   Updated: 2025/07/23 13:08:04 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	real_len;
	size_t	j;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		real_len = s_len - start;
	else
		real_len = len;
	sub = (char *) malloc(real_len + 1);
	if (!sub)
		return (NULL);
	j = -1;
	while (++j < real_len && s[start])
		sub[j] = s[start++];
	sub[j] = '\0';
	return (sub);
}
