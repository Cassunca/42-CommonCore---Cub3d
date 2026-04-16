/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shaders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:58:41 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/09 12:21:14 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "types.h"

void	draw_border(t_img *img, t_point pos, t_point size, int color)
{
	int	i;

	i = 0;
	while (i < size.x)
	{
		put_pixel(img, pos.x + i, pos.y, color);
		put_pixel(img, pos.x + i, pos.y + size.y, color);
		i++;
	}
	i = 0;
	while (i < size.y)
	{
		put_pixel(img, pos.x, pos.y + i, color);
		put_pixel(img, pos.x + size.x, pos.y + i, color);
		i++;
	}
}

void	draw_rect(t_img *img, t_point pos, t_point size, int color)
{
	int	i;
	int	j;

	i = pos.y;
	while (i < pos.y + size.y)
	{
		j = pos.x;
		while (j < pos.x + size.x)
		{
			put_pixel(img, j, i, color);
			j++;
		}
		i++;
	}
}

static void	init_line(t_line *l)
{
	l->dx = abs(l->x1 - l->x0);
	l->dy = abs(l->y1 - l->y0);
	if (l->x0 < l->x1)
		l->sx = 1;
	else
		l->sx = -1;
	if (l->y0 < l->y1)
		l->sy = 1;
	else
		l->sy = -1;
	l->err = l->dx - l->dy;
}

void	draw_line(t_img *img, t_line *l, int color)
{
	int	e2;

	init_line(l);
	while (TRUE)
	{
		put_pixel(img, l->x0, l->y0, color);
		if (l->x0 == l->x1 && l->y0 == l->y1)
			break ;
		e2 = 2 * l->err;
		if (e2 > -l->dy)
		{
			l->err -= l->dy;
			l->x0 += l->sx;
		}
		if (e2 < l->dx)
		{
			l->err += l->dx;
			l->y0 += l->sy;
		}
	}
}

void	draw_triangle(t_img *img, t_point pos, int size, int color)
{
	int		i;
	int		half;
	t_line	l;

	half = size / 2;
	i = 0;
	while (i <= half)
	{
		l = (t_line){
			.x0 = pos.x,
			.y0 = pos.y + half - i,
			.x1 = pos.x + i,
			.y1 = pos.y + half
		};
		draw_line(img, &l, color);
		l = (t_line){
			.x0 = pos.x,
			.y0 = pos.y + half + i,
			.x1 = pos.x + i,
			.y1 = pos.y + half
		};
		draw_line(img, &l, color);
		i++;
	}
}
