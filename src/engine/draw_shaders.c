/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:51:08 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/13 19:57:24 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_status_box(t_data *game, t_point pos, int input_x, int input_y)
{
	int	keypad_top;
	int	middle_y;
	int	rect_y;

	keypad_top = pos.y + 220;
	middle_y = (input_y + INPUT_H + keypad_top) / 2;
	rect_y = middle_y - (STATUS_H / 2);
	draw_shape(&game->frame, (t_shape){
		input_x, rect_y,
		INPUT_W, STATUS_H,
		5,
		0x0D1B22, 0x99DDFF, 2,
		SHAPE_RECT
	});
	return (rect_y);
}

void	draw_input_box(t_data *game, int x, int y)
{
	draw_shape(&game->frame, (t_shape){
		x, y,
		INPUT_W, INPUT_H,
		12,
		0x081218, 0x99DDFF, 2,
		SHAPE_RECT
	});
}

void	draw_box(t_data *game, t_point pos)
{
	draw_shape(&game->frame, (t_shape){
		pos.x, pos.y,
		PANEL_W, PANEL_H,
		20,
		0x060f20, 0x00FFFF, 2,
		SHAPE_RECT
	});
}
