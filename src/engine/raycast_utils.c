/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:11:19 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/15 19:04:42 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	fps(void)
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

void	str_num(t_data *game, int num, char *str, int x)
{
	char	*moves;
	char	*frase;

	moves = ft_itoa(num);
	frase = ft_strjoin(str, moves);
	mlx_string_put(game->mlx, game->win, x, 10, 0xFFFFFF, frase);
	free(moves);
	free(frase);
}

int	handle_door_hit(t_data *data)
{
	char	tile;
	t_door	*door;
	double	wall_x;
	double	door_size;

	tile = data->map.grid[data->ray.map_y][data->ray.map_x];
	if (tile != 'D' && tile != 'L')
		return (0);
	door = find_door(data, data->ray.map_x, data->ray.map_y);
	if (!door)
		return (0);
	if (door->open >= 0.99)
		return (0);
	if (data->ray.side == 0)
		wall_x = data->player.pos_y
			+ data->ray.wall_dist * data->ray.ray_dir_y;
	else
		wall_x = data->player.pos_x
			+ data->ray.wall_dist * data->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	door_size = (1.0 - door->open) * 0.5;
	if (wall_x > door_size && wall_x < (1.0 - door_size))
		return (0);
	return (1);
}

void	draw_info_door(t_data *data)
{
	t_door	*door;
	double	dx;
	double	dy;
	double	dist;

	door = get_door_in_sight(data);
	if (!door)
		return ;
	if (door->opening != 0)
		return ;
	dx = data->player.pos_x - (door->x + 0.5);
	dy = data->player.pos_y - (door->y + 0.5);
	dist = sqrt(dx * dx + dy * dy);
	if (door->open > 0.5 && dist < 0.6)
		return ;
	if (door->open < 0.9)
		mlx_string_put(data->mlx, data->win,
			WIN_WIDTH / 2 - 50,
			WIN_HEIGHT / 2 + 40,
			0xFFFFFF, "[SPACE] Open");
	else if (door->open > 0.1)
		mlx_string_put(data->mlx, data->win,
			WIN_WIDTH / 2 - 50,
			WIN_HEIGHT / 2 + 40,
			0xFFFFFF, "[SPACE] Close");
}
