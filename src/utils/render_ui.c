/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:02:15 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/08 20:02:53 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_button(t_data *g, t_button *btn)
{
	int border;

	if (btn->is_hover)
	{
		border = 0x802820;
		draw_rect(&g->frame, btn->x, btn->y, btn->w, btn->h, 0x1A0D0D);
	}
	else
	{
		border = 0x444455;
	}
	draw_border(&g->frame, btn->x, btn->y, btn->w, btn->h, border);
	draw_triangle(&g->frame,
		btn->x + 10,
		btn->y + btn->h / 2 - 5,
		10,
		0x802820);
}

void	draw_text_button(t_data *g, t_button *btn)
{
	int		color;

	if (btn->is_hover)
		color = 0xFFFFFF;
	else
		color = 0xAAAAAA;
	mlx_string_put(g->mlx, g->win,
		btn->x + 28,
		btn->y + btn->h / 2 + 4,
		color,
		btn->render_text);
}

void	draw_panel(t_img *img, int w, int h)
{
	int start_x;
	int start_y;
	int	y;
	int	x;

	start_x = (img->width - w) / 2;
	start_y = (img->height - h) / 2;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			put_pixel(img, start_x + x, start_y + y, 0x080812);
			if (x == 0 || x == w - 1 || y == 0 || y == h - 1)
				put_pixel(img, start_x + x, start_y + y, 0x2A2A3A);
			if (y == 0)
				put_pixel(img, start_x + x, start_y + y, 0x801E1E);
			x++;
		}
		y++;
	}
}

