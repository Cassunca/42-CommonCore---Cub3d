/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:02:15 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/09 12:58:13 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	draw_button(t_data *g, t_button *btn)
{
	int		border;
	t_point	pos;
	t_point	size;

	pos.x = btn->x;
	pos.y = btn->y;
	size.y = btn->h;
	size.x = btn->w;
	if (btn->is_hover)
	{
		border = 0x802820;
		draw_rect(&g->frame, pos, size, 0x1A0D0D);
	}
	else
	{
		border = 0x444455;
	}
	draw_border(&g->frame, pos, size, border);
	pos.x += 10;
	pos.y += btn->h / 2 - 5;
	draw_triangle(&g->frame,
		pos,
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
	int	start_x;
	int	start_y;
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

static t_line	make_line(int x0, int y0, int x1, int y1)
{
	t_line	l;

	l.x0 = x0;
	l.y0 = y0;
	l.x1 = x1;
	l.y1 = y1;
	return (l);
}

void	draw_lines(t_data *game, int panel_w, int panel_y)
{
	t_line	l;

	l = make_line((game->frame.width - (panel_w - 30)) / 2, panel_y + 135,
			(game->frame.width - (panel_w - 30)) / 2 + (panel_w - 30),
			panel_y + 135);
	draw_line(&game->frame, &l, 0x445566);
	l = make_line((game->frame.width - (panel_w - 30)) / 2, panel_y + 415,
			(game->frame.width - (panel_w - 30)) / 2 + (panel_w - 30),
			panel_y + 415);
	draw_line(&game->frame, &l, 0x445566);
}
