/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:19:37 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/12 23:37:41 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_doors(t_data	*game)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].opening != 0)
		{
			game->doors[i].open += game->doors[i].opening * 0.05;
			if (game->doors[i].open >= 1.0)
			{
				game->doors[i].open = 1.0;
				game->doors[i].opening = 0;
			}
			if (game->doors[i].open <= 0)
			{
				game->doors[i].open = 0.0;
				game->doors[i].opening = 0;
			}
		}
		i++;
	}
}

t_door	*find_door(t_data *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (&game->doors[i]);
		i++;
	}
	return (NULL);
}

t_door	*get_door_in_sight(t_data *game)
{
	double	dist;
	int		x;
	int		y;
	char	tile;
	t_door	*door;

	dist = 0;
	while (dist < 1.5)
	{
		x = (int)(game->player.pos_x + game->player.dir_x * dist);
		y = (int)(game->player.pos_y + game->player.dir_y * dist);
		tile = game->map.grid[y][x];
		door = find_door(game, x, y);
		if (door)
			return (door);
		if (tile == '1')
			return (NULL);
		dist += 0.05;
	}
	return (NULL);
}

void	open_door(t_data *game)
{
	t_door	*door;
	double	dx;
	double	dy;
	double	dist;

	door = get_door_in_sight(game);
	if (!door)
		return ;
	if (door->opening != 0)
		return ;
	dx = game->player.pos_x - (door->x + 0.5);
	dy = game->player.pos_y - (door->y + 0.5);
	dist = sqrt(dx * dx + dy * dy);
	if (door->open > 0.5 && dist < 0.6)
		return ;
	if (door->type == DOOR_NORMAL)
	{
		if (door->open < 0.5)
			door->opening = 1;
		else
			door->opening = -1;
	}
	else if (door->type == DOOR_SECRET)
		handle_secret_door(game, door);
}

void	init_doors(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	game->door_count = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'D' || game->map.grid[y][x] == 'S')
			{
				game->doors[game->door_count].x = x;
				game->doors[game->door_count].y = y;
				game->doors[game->door_count].open = 0.0;
				game->doors[game->door_count].opening = 0;
				game->doors[game->door_count].type = DOOR_NORMAL;
				if (game->map.grid[y][x] == 'S')
					game->doors[game->door_count].type = DOOR_SECRET;
				game->door_count++;
			}
			x++;
		}
		y++;
	}
}
