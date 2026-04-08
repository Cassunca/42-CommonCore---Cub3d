/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:42:50 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/08 18:08:50 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static int	in_circle(int px, int py)
{
	int	dx;
	int	dy;
	int	r;

	dx = px - MINI_X;
	dy = py - MINI_Y;
	r = MINI_RADIUS * MINI_CELL;
	return (dx * dx + dy * dy <= r * r);
}

static int	get_cell_color(t_data *data, int map_x, int map_y)
{
	char	tile;
	t_door	*door;

	if (map_x < 0 || map_y < 0 || map_x >= data->map.width
		|| map_y >= data->map.height)
		return (0x000000);
	tile = data->map.grid[map_y][map_x];
	if (tile == '1')
		return (0xFFFFFF);
	if (tile == 'D')
	{
		door = find_door(data, map_x, map_y);
		if (door && door->open > 0.8)
			return (0x222222);
		return (0xAA5500);
	}
	if (tile == 'S')
		return (0x8844FF);
	return (0x444444);
}

static void	draw_radar_circle(t_data *data)
{
	int	px;
	int	py;
	int	map_x;
	int	map_y;

	py = MINI_Y - MINI_RADIUS * MINI_CELL;
	while (py <= MINI_Y + MINI_RADIUS * MINI_CELL)
	{
		px = MINI_X - MINI_RADIUS * MINI_CELL;
		while (px <= MINI_X + MINI_RADIUS * MINI_CELL)
		{
			if (in_circle(px, py))
			{
				map_x = (double)data->player.pos_x
					+ (double)(px - MINI_X) / MINI_CELL;
				map_y = (double)data->player.pos_y
					+ (double)(py - MINI_Y) / MINI_CELL;
				my_mlx_pixel_put(&data->frame, px, py,
					get_cell_color(data, map_x, map_y));
			}
			px++;
		}
		py++;
	}
}

static void	draw_radar_player(t_data *data)
{
	int	i;
	int	px;
	int	py;

	py = -1;
	while (py <= 1)
	{
		px = -1;
		while (px <= 1)
		{
			my_mlx_pixel_put(&data->frame, MINI_X + px, MINI_Y + py, 0x00FF00);
			px++;
		}
		py++;
	}
	i = 0;
	while (i < MINI_CELL * 2)
	{
		px = MINI_X + (int)(data->player.dir_x * i);
		py = MINI_Y + (int)(data->player.dir_y * i);
		my_mlx_pixel_put(&data->frame, px, py, 0x00FF00);
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	draw_radar_circle(data);
	draw_radar_player(data);
}
