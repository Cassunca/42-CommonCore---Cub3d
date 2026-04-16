/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:48:38 by kamys             #+#    #+#             */
/*   Updated: 2026/03/28 17:50:29 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool	normalize_map(t_map *map)
{
	int		y;

	map->visualizer = malloc(sizeof(char *) * (map->height + 1));
	if (!map->visualizer)
		return (erro_int("malloc\n", FALSE));
	y = 0;
	while (y < map->height)
	{
		map->visualizer[y] = malloc(sizeof(char) * map->width + 1);
		if (!map->visualizer[y])
		{
			free_matrix(map->visualizer);
			return (erro_int("Normalize fail\n", FALSE));
		}
		ft_memset(map->visualizer[y], ' ', map->width);
		ft_memmove(map->visualizer[y], map->grid[y], ft_strlen(map->grid[y]));
		map->visualizer[y][map->width] = '\0';
		y++;
	}
	map->visualizer[map->height] = NULL;
	return (TRUE);
}

static void	set_player_dir(t_player *player, char dir)
{
	if (dir == 'N')
		set_vec2(0, -1, &player->dir_x, &player->dir_y);
	else if (dir == 'S')
		set_vec2(0, 1, &player->dir_x, &player->dir_y);
	else if (dir == 'E')
		set_vec2(1, 0, &player->dir_x, &player->dir_y);
	else if (dir == 'W')
		set_vec2(-1, 0, &player->dir_x, &player->dir_y);
	player->plane_x = -player->dir_y * player->fov;
	player->plane_y = player->dir_x * player->fov;
}

static void	find_to_player(t_map *map, t_player *player, t_point *pt)
{
	pt->y = 0;
	while (pt->y < map->height)
	{
		pt->x = 0;
		while (pt->x < map->width)
		{
			if (is_player(map->visualizer[pt->y][pt->x]))
			{
				player->pos_x = pt->x + 0.5;
				player->pos_y = pt->y + 0.5;
				player->fov = 0.66;
				set_player_dir(player, map->visualizer[pt->y][pt->x]);
				return ;
			}
			pt->x++;
		}
		pt->y++;
	}
}

static t_bool	flood_fill(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || map->height <= y || map->width <= x)
		return (FALSE);
	if (map->visualizer[y][x] == ' ')
		return (FALSE);
	if (map->visualizer[y][x] == '1' || map->visualizer[y][x] == 'F')
		return (TRUE);
	map->visualizer[y][x] = 'F';
	if (!flood_fill(map, y, x + 1))
		return (FALSE);
	if (!flood_fill(map, y, x - 1))
		return (FALSE);
	if (!flood_fill(map, y + 1, x))
		return (FALSE);
	if (!flood_fill(map, y - 1, x))
		return (FALSE);
	return (TRUE);
}

t_bool	parser_map(t_data *game)
{
	t_point	player;

	if (!normalize_map(&game->map))
		return (FALSE);
	find_to_player(&game->map, &game->player, &player);
	if (!flood_fill(&game->map, player.y, player.x))
		return (erro_int("Map open", FALSE));
	return (TRUE);
}
