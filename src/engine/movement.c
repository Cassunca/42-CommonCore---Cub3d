/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:01:56 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/08 18:20:17 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move_to(t_data *data, int x, int y)
{
	char	tile;
	t_door	*door;

	tile = data->map.grid[y][x];
	if (tile == '1')
		return (0);
	if (tile == 'D' || tile == 'S')
	{
		door = find_door(data, x, y);
		if (door && door->open < 0.8)
			return (0);
	}
	return (1);
}

static void	apply_side_translation(t_data *data, t_player *p)
{
	int	new_x;
	int	new_y;

	if (p->move_l)
	{
		new_x = (int)(p->pos_x + p->dir_y * MOVE_SPEED);
		new_y = (int)(p->pos_y);
		if (can_move_to(data, new_x, new_y))
			p->pos_x += p->dir_y * MOVE_SPEED;
		new_x = (int)(p->pos_x);
		new_y = (int)(p->pos_y - p->dir_x * MOVE_SPEED);
		if (can_move_to(data, new_x, new_y))
			p->pos_y -= p->dir_x * MOVE_SPEED;
	}
	if (p->move_r)
	{
		new_x = (int)(p->pos_x - p->dir_y * MOVE_SPEED);
		new_y = (int)(p->pos_y);
		if (can_move_to(data, new_x, new_y))
			p->pos_x -= p->dir_y * MOVE_SPEED;
		new_x = (int)(p->pos_x);
		new_y = (int)(p->pos_y + p->dir_x * MOVE_SPEED);
		if (can_move_to(data, new_x, new_y))
			p->pos_y += p->dir_x * MOVE_SPEED;
	}
}

static void	apply_translation(t_data *data, t_player *p)
{
	int	new_x;
	int	new_y;

	if (p->move_f)
	{
		new_x = (int)(p->pos_x + p->dir_x * MOVE_SPEED);
		new_y = (int)(p->pos_y);
		if (can_move_to(data, new_x, new_y))
			p->pos_x += p->dir_x * MOVE_SPEED;
		new_x = (int)(p->pos_x);
		new_y = (int)(p->pos_y + p->dir_y * MOVE_SPEED);
		if (can_move_to(data, new_x, new_y))
			p->pos_y += p->dir_y * MOVE_SPEED;
	}
	if (p->move_b)
	{
		new_x = (int)(p->pos_x - p->dir_x * MOVE_SPEED);
		new_y = (int)(p->pos_y);
		if (can_move_to(data, new_x, new_y))
			p->pos_x -= p->dir_x * MOVE_SPEED;
		new_x = (int)(p->pos_x);
		new_y = (int)(p->pos_y - p->dir_y * MOVE_SPEED);
		if (can_move_to(data, new_x, new_y))
			p->pos_y -= p->dir_y * MOVE_SPEED;
	}
}

void	apply_rotation(t_player *p, double speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
	p->dir_y = old_dir_x * sin(speed) + p->dir_y * cos(speed);
	p->plane_x = p->plane_x * cos(speed) - p->plane_y * sin(speed);
	p->plane_y = old_plane_x * sin(speed) + p->plane_y * cos(speed);
}

void	move_player(t_data *data)
{
	apply_translation(data, &data->player);
	apply_side_translation(data, &data->player);
	if (data->player.rot_l)
		apply_rotation(&data->player, -ROT_SPEED);
	if (data->player.rot_r)
		apply_rotation(&data->player, ROT_SPEED);
}
