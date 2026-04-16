/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:06:05 by kamys             #+#    #+#             */
/*   Updated: 2026/04/13 00:33:36 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static float	sdf_round_rect(t_vec2 p, t_rect r)
{
	float	dx;
	float	dy;
	float	ax;
	float	ay;

	dx = fabsf(p.x - r.center.x) - (r.size.x / 2.0f - r.radius);
	dy = fabsf(p.y - r.center.y) - (r.size.y / 2.0f - r.radius);
	ax = fmaxf(dx, 0.0f);
	ay = fmaxf(dy, 0.0f);
	return (sqrtf(ax * ax + ay * ay)
		+ fminf(fmaxf(dx, dy), 0.0f)
		- r.radius);
}

static float	sdf_circle(t_vec2 p, t_circle c)
{
	float	dx;
	float	dy;

	dx = p.x - c.center.x;
	dy = p.y - c.center.y;
	return (sqrtf(dx * dx + dy * dy) - c.radius);
}

static float	get_shape_distance(int x, int y, t_shape s)
{
	float	r;
	float	cx;
	float	cy;

	cx = s.x + s.w / 2.0f;
	cy = s.y + s.h / 2.0f;
	if (s.type == SHAPE_RECT)
		return (sdf_round_rect((t_vec2){x, y},
			(t_rect){(t_vec2){cx, cy}, (t_vec2){s.w, s.h}, s.radius}));
	if (s.w < s.h)
		r = s.w / 2.0f;
	else
		r = s.h / 2.0f;
	return (sdf_circle((t_vec2){x, y}, (t_circle){(t_vec2){cx, cy}, r}));
}

static int	get_shape_color(float d, t_shape s)
{
	if (d >= 0)
		return (0);
	if (s.border_thickness > 0
		&& fabsf(d) < s.border_thickness && s.border_color)
		return (s.border_color);
	return (s.fill_color);
}

void	draw_shape(t_img *img, t_shape s)
{
	int		color;
	int		px;
	int		py;
	float	d;

	py = s.y;
	while (py < s.y + s.h)
	{
		px = s.x;
		while (px < s.x + s.w)
		{
			d = get_shape_distance(px, py, s);
			color = get_shape_color(d, s);
			if (color)
				put_pixel(img, px, py, color);
			px++;
		}
		py++;
	}
}
