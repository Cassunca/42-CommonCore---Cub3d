/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 00:30:35 by kamys             #+#    #+#             */
/*   Updated: 2026/03/15 13:17:29 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_extension(char *path)
{
	int	len;
	int	len_extension;

	len_extension = ft_strlen(EXTENSION);
	len = ft_strlen(path);
	if (len <= len_extension)
		return (FALSE);
	return (!ft_strncmp(path + (len - len_extension), EXTENSION, len_extension));
}

static int	count_lines(char *path)
{
	char	*line;
	int		fd;
	int		lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (erro_int("could not open the file\n", -1));
	line = get_next_line(fd);
	lines = 0;
	while (line)
	{
		free(line);
		lines++;
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static char	**load_file_content(int lines, char *path)
{
	char	**file;
	char	*line;
	int		len;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (erro_matrix("could not open the file\n"));
	file = malloc(sizeof(char *) * (lines + 1));
	if (!file)
		return (erro_matrix("malloc failed\n"));
	line = get_next_line(fd);
	lines = 0;
	while (line)
	{
		file[lines++] = line;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		line = get_next_line(fd);
	}
	file[lines] = NULL;
	close(fd);
	return (file);
}

char	**read_file(char *path)
{
	int		lines;

	if (!check_extension(path))
		return (erro_matrix("file must have " EXTENSION " extension\n"));
	lines = count_lines(path);
	if (lines == -1)
		return (NULL);
	return (load_file_content(lines, path));
}
