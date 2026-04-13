/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:28:41 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/13 12:46:15 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TILE_WALL      0x01
#define TILE_SECRET    0x02
#define TILE_DECIDED   0x04

int	is_near_door(t_data *data, int x, int y)
{
	if (x > 0 && data->map.grid[y][x - 1] == 'D')
		return (1);
	if (x < data->map.width - 1 && data->map.grid[y][x + 1] == 'D')
		return (1);
	if (y > 0 && data->map.grid[y - 1][x] == 'D')
		return (1);
	if (y < data->map.height - 1 && data->map.grid[y + 1][x] == 'D')
		return (1);
	return (0);
}

int	has_door_left(t_data *d, int x, int y)
{
	return (x > 0 && d->map.grid[y][x - 1] == 'D');
}

int	has_door_right(t_data *d, int x, int y)
{
	return (x < d->map.width - 1 && d->map.grid[y][x + 1] == 'D');
}

int	has_door_up(t_data *d, int x, int y)
{
	return (y > 0 && d->map.grid[y - 1][x] == 'D');
}

int	has_door_down(t_data *d, int x, int y)
{
	return (y < d->map.height - 1 && d->map.grid[y + 1][x] == 'D');
}

t_img	*get_wall_tex(t_data *data)
{
	char	tile;
	double	wall_x;
	int		x;
	int		y;

	x = data->ray.map_x;
	y = data->ray.map_y;
	if (data->ray.side == 0)
		wall_x = data->player.pos_y
			+ data->ray.wall_dist * data->ray.ray_dir_y;
	else
		wall_x = data->player.pos_x
			+ data->ray.wall_dist * data->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	if (data->ray.side == 0 && data->ray.step_x > 0)
		wall_x = 1.0 - wall_x;
	if (data->ray.side == 1 && data->ray.step_y < 0)
		wall_x = 1.0 - wall_x;
	tile = data->map.grid[data->ray.map_y][data->ray.map_x];
	if (tile == 'D')
		return (&data->door_tex);
	if (tile == 'S')
		return (&data->secret_door);
	if (tile == '1')
	{
		if (data->ray.side == 0)
		{
			if (data->ray.step_x > 0)
			{
				if (has_door_left(data, x, y))
					return (&data->door_tex);
			}
			else
			{
				if (has_door_right(data, x, y))
					return (&data->door_tex);
			}
		}
		if (data->ray.side == 1)
		{
			if (data->ray.step_y > 0)
			{
				if (has_door_up(data, x, y))
					return (&data->door_tex);
			}
			else
			{
				if (has_door_down(data, x, y))
					return (&data->door_tex);
			}
		}
	}
	if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
		return (&data->tex.ea);
	if (data->ray.side == 0 && data->ray.ray_dir_x < 0)
		return (&data->tex.we);
	if (data->ray.side == 1 && data->ray.ray_dir_y > 0)
		return (&data->tex.so);
	return (&data->tex.no);
}

int	get_tex_pixel(t_img *tex, int x, int y)
{
	char	*pixel;

	if (!tex || !tex->addr)
		return (erro_int("unloaded texture", FALSE));
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}

int	get_tex_x(t_data *data, t_img *tex)
{
	double	wall_x;
	int		tex_x;
	char	tile;
	t_door	*door;
	double	door_size;

	if (data->ray.side == 0)
		wall_x = data->player.pos_y
			+ data->ray.wall_dist * data->ray.ray_dir_y;
	else
		wall_x = data->player.pos_x
			+ data->ray.wall_dist * data->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	tile = data->map.grid[data->ray.map_y][data->ray.map_x];
	if (tile == 'D' || tile == 'S')
	{
		door = find_door(data, data->ray.map_x, data->ray.map_y);
		if (door && door->open < 0.99)
		{
			door_size = (1.0 - door->open) * 0.5;
			if (door_size < 0.001)
				door_size = 0.001;
			if (wall_x <= door_size)
				wall_x = wall_x / door_size;
			else
				wall_x = (wall_x - (1.0 - door_size)) / door_size;
		}
	}
	tex_x = (int)(wall_x * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (data->ray.side == 0 && data->ray.step_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (data->ray.side == 1 && data->ray.step_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

// int	get_tex_x(t_data *data, t_img *tex)
// {
// 	double	wall_x;
// 	int		tex_x;

// 	if (data->ray.side == 0)
// 		wall_x = data->player.pos_y + data->ray.wall_dist * data->ray.ray_dir_y;
// 	else
// 		wall_x = data->player.pos_x + data->ray.wall_dist * data->ray.ray_dir_x;
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * tex->width);
// 	if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
// 		tex_x = tex->width - tex_x - 1;
// 	if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
// 		tex_x = tex->width - tex_x - 1;
// 	return (tex_x);
// }
