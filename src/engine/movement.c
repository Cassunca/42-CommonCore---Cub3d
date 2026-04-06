/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:01:56 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/06 14:50:15 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_side_translation(t_data *data, t_player *p)
{
	if (p->move_l)
	{
		if (data->map.grid[(int)p->pos_y]
			[(int)(p->pos_x + p->dir_y * MOVE_SPEED)] != '1')
			p->pos_x += p->dir_y * MOVE_SPEED;
		if (data->map.grid[(int)(p->pos_y - p->dir_x * MOVE_SPEED)]
			[(int)p->pos_x] != '1')
			p->pos_y -= p->dir_x * MOVE_SPEED;
	}
	if (p->move_r)
	{
		if (data->map.grid[(int)p->pos_y]
			[(int)(p->pos_x - p->dir_y * MOVE_SPEED)] != '1')
			p->pos_x -= p->dir_y * MOVE_SPEED;
		if (data->map.grid[(int)(p->pos_y + p->dir_x * MOVE_SPEED)]
			[(int)p->pos_x] != '1')
			p->pos_y += p->dir_x * MOVE_SPEED;
	}
}

static void	apply_translation(t_data *data, t_player *p)
{
	if (p->move_f)
	{
		if (data->map.grid[(int)p->pos_y]
			[(int)(p->pos_x + p->dir_x * MOVE_SPEED)] != '1')
			p->pos_x += p->dir_x * MOVE_SPEED;
		if (data->map.grid[(int)(p->pos_y + p->dir_y * MOVE_SPEED)]
			[(int)p->pos_x] != '1')
			p->pos_y += p->dir_y * MOVE_SPEED;
	}
	if (p->move_b)
	{
		if (data->map.grid[(int)p->pos_y]
			[(int)(p->pos_x - p->dir_x * MOVE_SPEED)] != '1')
			p->pos_x -= p->dir_x * MOVE_SPEED;
		if (data->map.grid[(int)(p->pos_y - p->dir_y * MOVE_SPEED)]
			[(int)p->pos_x] != '1')
			p->pos_y -= p->dir_y * MOVE_SPEED;
	}
	if (p->move_l || p->move_r)
		apply_side_translation(data, &data->player);
}

static void	apply_rotation(t_player *p, double speed)
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
	if (data->player.rot_l)
		apply_rotation(&data->player, -ROT_SPEED);
	if (data->player.rot_r)
		apply_rotation(&data->player, ROT_SPEED);
}
