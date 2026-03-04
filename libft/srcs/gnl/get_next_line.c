/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:17:07 by amyrodri          #+#    #+#             */
/*   Updated: 2025/08/24 12:00:48 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	new_line(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*extract_line_and_stash(char *line, char **stash)
{
	char	*new_line;
	int		i;

	if (!line || line[0] == '\0')
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	new_line = ft_substr(line, 0, i);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	if (line[i] != '\0')
		*stash = ft_strdup(line + i);
	else
		*stash = NULL;
	free(line);
	return (new_line);
}

void	*free_null(char *buffer, char *line)
{
	free(buffer);
	free(line);
	return (NULL);
}

char	*read_line(char *line, int fd)
{
	int		bytes;
	char	*buffer;
	char	*tmp;

	if (!line)
		line = ft_strdup("");
	buffer = malloc (BUFFER_SIZE + 1);
	if (!buffer || !line)
		return (free_null(buffer, line));
	bytes = 1;
	while (!new_line(line) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free_null(buffer, line));
		buffer[bytes] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		if (!tmp)
			return (free_null(buffer, tmp));
		line = tmp;
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash[fd])
	{
		line = ft_strdup(stash[fd]);
		free(stash[fd]);
		stash[fd] = NULL;
	}
	else
		line = NULL;
	line = read_line(line, fd);
	if (!line)
		return (free(stash[fd]), stash[fd] = NULL);
	if (new_line(line))
		line = extract_line_and_stash(line, &stash[fd]);
	else
		stash[fd] = NULL;
	if (!line || *line == '\0')
		return (free(line), free(stash[fd]), stash[fd] = NULL);
	return (line);
}
