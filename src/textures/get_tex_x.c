/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:00:20 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/15 19:04:18 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_wall_x(t_data *data)
{
	double	wall_x;

	if (data->ray.side == 0)
		wall_x = data->player.pos_y
			+ data->ray.wall_dist * data->ray.ray_dir_y;
	else
		wall_x = data->player.pos_x
			+ data->ray.wall_dist * data->ray.ray_dir_x;
	return (wall_x - floor(wall_x));
}

static double	apply_door(t_data *data, double wall_x)
{
	t_door	*door;
	char	tile;
	double	door_size;

	tile = data->map.grid[data->ray.map_y][data->ray.map_x];
	if (tile != 'D' && tile != 'S')
		return (wall_x);
	door = find_door(data, data->ray.map_x, data->ray.map_y);
	if (!door || door->open >= 0.99)
		return (wall_x);
	door_size = (1.0 - door->open) * 0.5;
	if (door_size < 0.001)
		door_size = 0.001;
	if (wall_x <= door_size)
		wall_x = wall_x / door_size;
	else
		wall_x = (wall_x - (1.0 - door_size)) / door_size;
	return (wall_x);
}

int	sla(t_data *data, int invert)
{
	double	original_x;
	char	tile;
	int		is_right_half;

	tile = data->map.grid[data->ray.map_y][data->ray.map_x];
	original_x = get_wall_x(data);
	if (tile == 'D' || tile == 'L')
	{
		is_right_half = (original_x >= 0.5);
		if (data->ray.side == 0)
		{
			if (data->ray.ray_dir_x < 0)
				is_right_half = !is_right_half;
		}
		else
		{
			if (data->ray.ray_dir_y > 0)
				is_right_half = !is_right_half;
		}
		if (is_right_half)
			invert = !invert;
	}
	return (invert);
}

int	get_tex_x(t_data *data, t_img *tex)
{
	double	wall_x;
	int		tex_x;
	int		invert;

	wall_x = get_wall_x(data);
	wall_x = apply_door(data, wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	invert = ((data->ray.side == 0 && data->ray.step_x > 0)
			|| (data->ray.side == 1 && data->ray.step_y < 0));
	if (sla(data, invert))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
