/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:53:20 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/15 18:20:35 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_pixel(t_img *img, int x, int y);
void	sort_sprites(t_data *g);
void	get_dist_object(t_data *g);

static int	transform_sprite(t_data *g, t_sprite *s,
		double *tx, double *ty)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = s->x - g->player.pos_x;
	sprite_y = s->y - g->player.pos_y;
	inv_det = 1.0 / (g->player.plane_x * g->player.dir_y
			- g->player.dir_x * g->player.plane_y);
	*tx = inv_det * (g->player.dir_y * sprite_x
			- g->player.dir_x * sprite_y);
	*ty = inv_det * (-g->player.plane_y * sprite_x
			+ g->player.plane_x * sprite_y);
	return (*ty > 0);
}

static void	get_sprite_size(t_data *g, t_context *t)
{
	t->h = abs((int)(g->frame.height / t->ty));
	t->w = t->h * ((double)t->tex->width / t->tex->height);
	t->h *= 0.6;
	t->w *= 0.6;
}

static void	clamp(int *start, int *end, int max)
{
	if (*start < 0)
		*start = 0;
	if (*end >= max)
		*end = max - 1;
}

static void	draw_sprite_stripes(t_data *g, t_context t)
{
	t_point	tex;
	int		y;
	int		stripe;

	stripe = t.start.x;
	while (stripe < t.end.x)
	{
		tex.x = (int)(256 * (stripe - (-t.w / 2 + t.screen_x))
				* t.tex->width / t.w) / 256;
		if (t.ty > 0 && stripe > 0 && stripe < g->frame.width
			&& t.ty < g->zbuffer[stripe])
		{
			y = t.start.y;
			while (y < t.end.y)
			{
				tex.y = ((y * 256 - g->frame.height * 128 + t.h * 128)
						* t.tex->height / t.h) / 256;
				if (get_pixel(t.tex, tex.x, tex.y) != 0x000000)
					put_pixel(&g->frame, stripe, y,
						get_pixel(t.tex, tex.x, tex.y));
				y++;
			}
		}
		stripe++;
	}
}

void	draw_sprites(t_data *g)
{
	int			i;
	t_context	test;

	i = 0;
	while (i < g->sprite_count)
	{
		test.tex = &g->sprites[i].frames[g->sprites[i].current_frame];
		if (!transform_sprite(g, &g->sprites[i], &test.tx, &test.ty))
		{
			i++;
			continue ;
		}
		test.screen_x = (int)((g->frame.width / 2) * (1 + test.tx / test.ty));
		get_sprite_size(g, &test);
		test.start.y = -test.h / 2 + g->frame.height / 2;
		test.end.y = test.h / 2 + g->frame.height / 2;
		test.start.x = -test.w / 2 + test.screen_x;
		test.end.x = test.w / 2 + test.screen_x;
		clamp(&test.start.y, &test.end.y, g->frame.height);
		clamp(&test.start.x, &test.end.x, g->frame.width);
		draw_sprite_stripes(g, test);
		i++;
	}
}
