/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:41:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/02 22:18:28 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fps_limiter(double current, double fps)
{
	double	frame_end;
	double	frame_duration;
	double	target_frame_time;

	if (fps == 0.0)
		return ;
	frame_end = get_time();
	frame_duration = frame_end - current;
	target_frame_time = 1.0 / fps;
	if (frame_duration < target_frame_time)
		my_usleep(target_frame_time - frame_duration);
}

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int brighten(int color, float factor)
{
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;

	r *= factor;
	g *= factor;
	b *= factor;

	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;

	return ((r << 16) | (g << 8) | b);
}

static void	draw_pixel_safe(t_data *game, t_img *sprite, t_point frame_pt,
							t_point sprite_pt, int is_hover)
{
	char	*src;
	int		color;

	if (frame_pt.x >= 0 && frame_pt.x < game->frame.width)
	{
		src = sprite->addr + (sprite_pt.y * sprite->line_len
				+ sprite_pt.x * (sprite->bpp / 8));
		color = *(int *)src;
		if ((color & 0x00FFFFFF) != 0xFF00FF)
		{
			if (is_hover)
				color = brighten(color, 1.2);
			put_pixel(&game->frame, frame_pt.x, frame_pt.y, color);
		}
	}
}

static void	draw_sprite_to_frame(t_data *game, t_img *sprite, int x, int y, int is_hover)
{
	t_point	frame_pt;
	t_point	sprite_pt;

	sprite_pt.y = 0;
	while (sprite_pt.y < sprite->height)
	{
		frame_pt.y = y + sprite_pt.y;
		if (frame_pt.y >= 0 && frame_pt.y < game->frame.height)
		{
			sprite_pt.x = 0;
			while (sprite_pt.x < sprite->width)
			{
				frame_pt.x = x + sprite_pt.x;
				draw_pixel_safe(game, sprite, frame_pt, sprite_pt, is_hover);
				sprite_pt.x++;
			}
		}
		sprite_pt.y++;
	}
}

void	draw_button(t_data *game, t_button *btn)
{
	// printf("%d\n", btn->is_hover);
	draw_sprite_to_frame(game, btn->img, btn->x, btn->y, btn->is_hover);
}

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

void	render(t_data *game, double alpha)
{
	(void)alpha;
	// render_background(game, game->colors.ceiling, game->colors.floor);
	draw_sky(game, game->colors.ceiling, game->colors.floor);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
}

void	draw_leaf_sprite(t_data *game, int frame, int x, int y)
{
	t_img *img = &game->leaf_frames[frame];

	draw_sprite_to_frame(game, img, x, y, 0);
	// mlx_put_image_to_window(game->mlx, game->win, img->ptr, x, y);
}

void	render_leaves(t_data *game, double alpha)
{
	for (int i = 0; i < MAX_LEAVES; i++)
	{
		t_leaf *l = &game->leaves[i];

		double	render_x = lerp(l->prev_x, l->x, alpha);
		double	render_y = lerp(l->prev_y, l->y, alpha);

		draw_leaf_sprite(game, l->frame, render_x, render_y);
	}
}

void render_title(t_data *game, double alpha)
{
	// render_background(game, 0x87CEEB, 0x8B4513);
	int y = (game->frame.height / 2);
	int x = (game->frame.width / 2);

	draw_sky(game, 0x001a66, 0x87CEEB);

	// for (int x = 0; x < game->frame.width; x++)
	// {
	// 	for (int y = 0; y < game->frame.height; y++)
	// 	{
	// 		if (x == game->frame.width / 2)
	// 			put_pixel(&game->frame, x, y, 0xFFFFFF);
	// 		if (y == game->frame.height / 2)			
	// 			put_pixel(&game->frame, x, y, 0xFFFFFF);
	// 	}
	// }
	
	render_leaves(game, alpha);

	
	draw_sprite_to_frame(game, &game->logo, x - (game->logo.width / 2), y - 100, 0);

	draw_button(game, &game->btn[0]);
	draw_button(game, &game->btn[1]);

	draw_sprite_to_frame(game, &game->logo_42, 770, 570, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	mlx_string_put(game->mlx, game->win, 10, 590, 0x000000, "By: Amyrodri and Cassunca");

	// mlx_string_put(game->mlx, game->win, 450, 340, 0xFFFFFF, "PLAY");
}

void	update_leaves(t_data *game, double dt)
{
	for (int i = 0; i < MAX_LEAVES; i++)
	{
		t_leaf *l = &game->leaves[i];

		l->prev_x = l->x;
		l->prev_y = l->y;

		l->time += dt;

		// cair
		l->y += l->speed_y * dt;

		// vento (movimento em S)
		l->x += sin(l->time * l->frequency) * l->amplitude * dt;

		// animação sprite
		l->anim_time += dt;
		if (l->anim_time > l->anim_speed)
		{
			l->frame += l->frame_dir;

			if (l->frame >= 4)
			{
				l->frame = 4;
				l->frame_dir = -1;
			}
			else if (l->frame <= 0)
			{
				l->frame = 0;
				l->frame_dir = 1;
			}

			l->anim_time -= l->anim_speed;
		}

		// reset
		if (l->y > WIN_HEIGHT)
			init_leaf(l);
	}
}

int game_loop(t_data *game)
{
	static double	accumulator = 0.0;
	static double	previos = 0.0;
	double			current;
	double			frame_time;
	const double	tick_rate = 1.0 / 240.0;

	if (previos == 0)
		previos = get_time();
	current = get_time();
	frame_time = current - previos;
	previos = current;
	if (frame_time > 0.25)
		frame_time = 0.25;
	accumulator += frame_time;
	while (accumulator >= tick_rate)
	{
		update_leaves(game, tick_rate);
		accumulator -= tick_rate;
	}
	mlx_clear_window(game->mlx, game->win);
	if (game->screen == TITLE)
		render_title(game, (accumulator / tick_rate));
	else if (game->screen == GAME)
		render(game, (accumulator / tick_rate));
	fps_limiter(current, 244.0);
	return (0);
}
