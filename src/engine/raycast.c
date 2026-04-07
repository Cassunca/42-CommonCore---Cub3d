/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:01:24 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/07 16:30:51 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (data->map.grid[data->ray.map_y][data->ray.map_x] == '1')
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

static double	fps(void)
{
	static double	last_time = 0;
	static double	fps = 0;
	static int		frames = 0;
	double			current_time;

	current_time = get_time();
	frames++;
	if (last_time == 0)
		last_time = current_time;
	if (current_time - last_time >= 1.0)
	{
		fps = frames / (current_time - last_time);
		last_time = current_time;
		frames = 0;
	}
	return (fps);
}

static void	str_num(t_data *game, int num, char *str, int x)
{
	char	*moves;
	char	*frase;

	moves = ft_itoa(num);
	frase = ft_strjoin(str, moves);
	mlx_string_put(game->mlx, game->win, x, 10, 0xFFFFFF, frase);
	free(moves);
	free(frase);
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
		x++;
	}
	str_num(data, (int)fps(), "fps: ", 200);
}
