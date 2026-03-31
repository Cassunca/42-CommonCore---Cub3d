/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 16:56:58 by kamys             #+#    #+#             */
/*   Updated: 2026/03/28 16:57:21 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool	test_tex(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (erro_int("Failed to open texture file", FALSE));
	close(fd);
	return (TRUE);
}

t_bool	parse_no(t_parser *p, char *line)
{
	char	*path;

	if (p->game->tex_path.no)
		return (write_erro("Duplicate NO"), FALSE);
	path = line + 3;
	path = ft_strtrim(path, " \t\n");
	if (!path)
		return (FALSE);
	if (!test_tex(path))
		return (FALSE);
	p->game->tex_path.no = path;
	return (TRUE);
}

t_bool	parse_so(t_parser *p, char *line)
{
	char	*path;

	if (p->game->tex_path.so)
		return (write_erro("Duplicate SO"), FALSE);
	path = line + 3;
	path = ft_strtrim(path, " \t\n");
	if (!path)
		return (FALSE);
	if (!test_tex(path))
		return (FALSE);
	p->game->tex_path.so = path;
	return (TRUE);
}

t_bool	parse_we(t_parser *p, char *line)
{
	char	*path;

	if (p->game->tex_path.we)
		return (write_erro("Duplicate we"), FALSE);
	path = line + 3;
	path = ft_strtrim(path, " \t\n");
	if (!path)
		return (FALSE);
	if (!test_tex(path))
		return (FALSE);
	p->game->tex_path.we = path;
	return (TRUE);
}

t_bool	parse_ea(t_parser *p, char *line)
{
	char	*path;

	if (p->game->tex_path.ea)
		return (write_erro("Duplicate EA"), FALSE);
	path = line + 3;
	path = ft_strtrim(path, " \t\n");
	if (!path)
		return (FALSE);
	if (!test_tex(path))
		return (FALSE);
	p->game->tex_path.ea = path;
	return (TRUE);
}
