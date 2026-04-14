/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:28:41 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/13 20:11:35 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TILE_WALL      0x01
#define TILE_SECRET    0x02
#define TILE_DECIDED   0x04

static t_bool	has_door(t_data *data, t_point pos, int dx, int dy)
{
	if (pos.y + dy < 0 || pos.x + dx < 0
		|| pos.y + dy >= data->map.height
		|| pos.x + dx >= data->map.width)
		return (FALSE);
	return (data->map.grid[pos.y + dy][pos.x + dx] == 'D');
}

static t_img	*get_special_tex(t_data *data, int x, int y)
{
	char	tile;

	tile = data->map.grid[y][x];
	if (tile == 'D')
		return (&data->door_tex);
	if (tile == 'S')
		return (&data->secret_door);
	if (tile == '1')
	{
		if (data->ray.side == 0)
		{
			if (data->ray.step_x > 0 && has_door(data, (t_point){x, y}, -1, 0))
				return (&data->door_tex);
			if (data->ray.step_x < 0 && has_door(data, (t_point){x, y}, 1, 0))
				return (&data->door_tex);
		}
		else
		{
			if (data->ray.step_y > 0 && has_door(data, (t_point){x, y}, 0, -1))
				return (&data->door_tex);
			if (data->ray.step_y < 0 && has_door(data, (t_point){x, y}, 0, 1))
				return (&data->door_tex);
		}
	}
	return (NULL);
}

static t_img	*get_direction_tex(t_data *data)
{
	if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
		return (&data->tex.ea);
	if (data->ray.side == 0 && data->ray.ray_dir_x < 0)
		return (&data->tex.we);
	if (data->ray.side == 1 && data->ray.ray_dir_y > 0)
		return (&data->tex.so);
	return (&data->tex.no);
}

t_img	*get_wall_tex(t_data *data)
{
	t_img	*tex;
	int		x;
	int		y;

	x = data->ray.map_x;
	y = data->ray.map_y;
	tex = get_special_tex(data, x, y);
	if (tex)
		return (tex);
	return (get_direction_tex(data));
}
