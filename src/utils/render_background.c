/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:01:33 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/08 20:02:02 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_gradient_color(int top, int bottom, float t)
{
	int	r[3];
	int	g[3];
	int	b[3];

	r[0] = (top >> 16) & 0xFF;
	g[0] = (top >> 8) & 0xFF;
	b[0] = top & 0xFF;
	r[1] = (bottom >> 16) & 0xFF;
	g[1] = (bottom >> 8) & 0xFF;
	b[1] = bottom & 0xFF;
	r[2] = r[0] + t * (r[1] - r[0]);
	g[2] = g[0] + t * (g[1] - g[0]);
	b[2] = b[0] + t * (b[1] - b[0]);
	return ((r[2] << 16) | (g[2] << 8) | b[2]);
}

void	draw_sky(t_data *game, int top_color, int bottom_color)
{
	t_point	pt;
	float	t;
	int		color;

	pt.y = 0;
	while (pt.y < game->frame.height)
	{
		t = (float)pt.y / (float)game->frame.height;
		color = get_gradient_color(top_color, bottom_color, t);
		pt.x = 0;
		while (pt.x < game->frame.width)
		{
			put_pixel(&game->frame, pt.x, pt.y, color);
			pt.x++;
		}
		pt.y++;
	}
}
