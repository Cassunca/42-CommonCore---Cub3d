/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:45:45 by kamys             #+#    #+#             */
/*   Updated: 2026/04/08 16:36:37 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool	copy_lines(t_map *map, t_parser *p)
{
	int	i;
	int	file_i;

	i = 0;
	file_i = p->i;
	while (i < map->height)
	{
		map->grid[i] = ft_strdup(p->file[file_i++]);
		if (!map->grid[i])
		{
			free_matrix(map->grid);
			return (erro_int("strdup\n", FALSE));
		}
		i++;
	}
	map->grid[map->height] = NULL;
	return (TRUE);
}

static int	get_effective_end(t_parser *p)
{
	int	file_i;

	file_i = p->i;
	while (p->file[file_i])
		file_i++;
	while (file_i > p->i && is_empty_line(p->file[file_i - 1]))
		file_i--;
	return (file_i);
}

static int	get_max_width(char **grid, int height)
{
	int	i;
	int	max;
	int	width;

	i = 0;
	max = 0;
	while (i < height)
	{
		width = ft_strlen(grid[i]);
		if (width > max)
			max = width;
		i++;
	}
	return (max);
}

static t_bool	copy_grid(t_map *map, t_parser *p)
{
	int	end;

	end = get_effective_end(p);
	map->height = end - p->i;
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (erro_int("malloc\n", FALSE));
	if (!copy_lines(map, p))
		return (FALSE);
	map->width = get_max_width(map->grid, map->height);
	return (TRUE);
}

t_bool	parser(char *file, t_data *game)
{
	t_parser	p;

	p.file = read_file(file);
	p.i = 0;
	p.config_count = 0;
	p.game = game;
	if (!p.file)
		return (destroy_game(game, &p), FALSE);
	if (!parser_configs(&p))
		return (destroy_game(game, &p), FALSE);
	if (!copy_grid(&p.game->map, &p))
		return (destroy_game(game, &p), FALSE);
	if (!parser_map(p.game))
		return (destroy_game(game, &p), FALSE);
	free_matrix(p.file);
	free_matrix(p.game->map.visualizer);
	return (TRUE);
}
