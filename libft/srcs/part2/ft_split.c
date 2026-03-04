/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:31:01 by amyrodri          #+#    #+#             */
/*   Updated: 2025/07/24 11:01:09 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(const char *s, char c)
{
	int	count;
	int	words;

	count = 0;
	words = 0;
	while (*s)
	{
		if (*s != c && words == 0)
		{
			words = 1;
			count++;
		}
		else if (*s == c)
			words = 0;
		s++;
	}
	return (count);
}

void	free_split(char **splits)
{
	int	k;

	k = -1;
	while (splits[++k])
		free(splits[k]);
	free(splits);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		start;
	int		i;
	int		k;

	split = ft_calloc(sizeof(char *), (count(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		split[k] = ft_substr(s, start, i - start);
		if (!split[k++])
			free_split(split);
	}
	split[k] = NULL;
	return (split);
}
