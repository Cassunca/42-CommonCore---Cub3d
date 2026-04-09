/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:19:37 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/09 13:59:38 by kamys            ###   ########.fr       */
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

void	open_door(t_data *game)
{
	int		target_x;
	int		target_y;
	t_door	*door;
	char	tile;

	target_x = (int)(game->player.pos_x + game->player.dir_x);
	target_y = (int)(game->player.pos_y + game->player.dir_y);
	tile = game->map.grid[target_y][target_x];
	door = find_door(game, target_x, target_y);
	if (door && tile == 'D')
	{
		if (door->open == 0.0)
			door->opening = 1;
		else
			door->opening = -1;
	}
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
		while (x < game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == 'D' || game->map.grid[y][x] == 'S')
			{
				game->doors[game->door_count].x = x;
				game->doors[game->door_count].y = y;
				game->doors[game->door_count].open = 0.0;
				game->doors[game->door_count].opening = 0;
				game->door_count++;
			}
			x++;
		}
		y++;
	}
}
