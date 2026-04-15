/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:01:24 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/15 16:57:34 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_info_door(t_data *data);
void	draw_sprites(t_data *g);
void	sort_sprites(t_data *g);
void	get_dist_object(t_data *g);

static void	set_dda_step(t_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.pos_x - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.pos_x)
			* data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.pos_y - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.pos_y)
			* data->ray.delta_dist_y;
	}
}

static void	calculate_line_height(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.wall_dist = data->ray.side_dist_x
			- data->ray.delta_dist_x;
	else
		data->ray.wall_dist = data->ray.side_dist_y
			- data->ray.delta_dist_y;
	data->ray.line_height = (int)(WIN_HEIGHT / data->ray.wall_dist);
	data->ray.draw_start = -data->ray.line_height / 2 + WIN_HEIGHT / 2;
	data->ray.draw_end = data->ray.line_height / 2 + WIN_HEIGHT / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	if (data->ray.draw_end >= WIN_HEIGHT)
		data->ray.draw_end = WIN_HEIGHT - 1;
}

static void	perform_dda(t_data *data)
{
	char	tile;

	data->ray.hit = 0;
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		tile = data->map.grid[data->ray.map_y][data->ray.map_x];
		if (tile == '1')
			data->ray.hit = 1;
		else if (handle_door_hit(data))
			data->ray.hit = 1;
	}
}

static void	init_ray_info(t_data *data, int x)
{
	data->ray.camera_x = 2 * x / (double)WIN_WIDTH - 1;
	data->ray.ray_dir_x = data->player.dir_x + data->player.plane_x
		* data->ray.camera_x;
	data->ray.ray_dir_y = data->player.dir_y + data->player.plane_y
		* data->ray.camera_x;
	if (data->ray.ray_dir_x == 0)
		data->ray.delta_dist_x = 1e30;
	else
		data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	if (data->ray.ray_dir_y == 0)
		data->ray.delta_dist_y = 1e30;
	else
		data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
}

void	execute_raycast(t_data *data)
{
	int	x;

	x = 0;
	render_background(data);
	while (x < WIN_WIDTH)
	{
		init_ray_info(data, x);
		data->ray.map_x = (int)data->player.pos_x;
		data->ray.map_y = (int)data->player.pos_y;
		set_dda_step(data);
		perform_dda(data);
		calculate_line_height(data);
		draw_wall_column(data, x);
		data->zbuffer[x] = data->ray.wall_dist;
		x++;
	}
	get_dist_object(data);
	sort_sprites(data);
	draw_sprites(data);
	draw_minimap(data);
	draw_crosshair(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.ptr, 0, 0);
	draw_info_door(data);
	str_num(data, (int)fps(), "fps: ", 70);
}
