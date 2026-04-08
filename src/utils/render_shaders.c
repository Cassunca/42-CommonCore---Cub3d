/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shaders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:58:41 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/08 20:01:13 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_border(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;

	i = 0;
	while (i < w)
	{
		put_pixel(img, x + i, y, color);
		put_pixel(img, x + i, y + h, color);
		i++;
	}
	i = 0;
	while (i < h)
	{
		put_pixel(img, x, y + i, color);
		put_pixel(img, x + w, y + i, color);
		i++;
	}
}

void draw_rect(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + h)
	{
		j = x;
		while (j < x + w)
		{
			put_pixel(img, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (TRUE)
	{
		put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_triangle(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	half;

	half = size / 2;
	i = 0;
	while (i <= half)
	{
		draw_line(img,
			x,
			y + half - i,
			x + i,
			y + half,
			color);
		draw_line(img,
			x,
			y + half + i,
			x + i,
			y + half,
			color);
		i++;
	}
}

void	draw_line_fancy(t_img *img, int x, int y, int w)
{
	int	i;
	int color;

	i = 0;
	while (i < w)
	{
		if (i < 20)
			color = 0x222a38;
		else if (i > w - 20)
			color = 0x222a38;
		else
			color = 0x445566;
		put_pixel(img, x + i, y, color);
		i++;
	}
}

