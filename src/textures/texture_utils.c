/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:28:41 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/09 14:55:46 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_wall_tex(t_data *data)
{
	char	tile;

	tile = data->map.grid[data->ray.map_y][data->ray.map_x];
	if (tile == 'D')
		return (&data->door_tex);
	if (tile == 'S')
		return (&data->secret_door);
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

	if (data->ray.side == 0)
		wall_x = data->player.pos_y + data->ray.wall_dist * data->ray.ray_dir_y;
	else
		wall_x = data->player.pos_x + data->ray.wall_dist * data->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
