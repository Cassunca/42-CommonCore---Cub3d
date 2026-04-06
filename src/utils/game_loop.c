/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:41:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/04 22:30:13 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define PANEL_COLOR 0x121826
#define PANEL_BORDER 0x2A3142

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
	int r;
	int g;
	int b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r *= factor;
	g *= factor;
	b *= factor;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
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
	draw_sky(game, game->colors.ceiling, game->colors.floor);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
}

void	draw_leaf_sprite(t_data *game, int frame, int x, int y)
{
	t_img *img = &game->leaf_frames[frame];

	draw_sprite_to_frame(game, img, x, y, 0);
}

void	render_leaves(t_data *game, double alpha)
{
	int		i;
	double	render_x;
	double	render_y;
	t_leaf	*l;

	i = 0;
	while (i < MAX_LEAVES)
	{
		l = &game->leaves[i];
		render_x = lerp(l->prev_x, l->x, alpha);
		render_y = lerp(l->prev_y, l->y, alpha);
		draw_leaf_sprite(game, l->frame, render_x, render_y);
		i++;
	}
}

void draw_rect(t_img *img, int x, int y, int w, int h, int color)
{
	for (int i = y; i < y + h; i++)
		for (int j = x; j < x + w; j++)
			put_pixel(img, j, i, color);
}

void draw_border(t_img *img, int x, int y, int w, int h, int color)
{
	for (int i = 0; i < w; i++)
	{
		put_pixel(img, x + i, y, color);
		put_pixel(img, x + i, y + h, color);
	}
	for (int i = 0; i < h; i++)
	{
		put_pixel(img, x, y + i, color);
		put_pixel(img, x + w, y + i, color);
	}
}

void	draw_line_fancy(t_img *img, int x, int y, int w)
{
	for (int i = 0; i < w; i++)
	{
		int color;

		if (i < 20)
			color = 0x222a38;
		else if (i > w - 20)
			color = 0x222a38;
		else
			color = 0x445566;

		put_pixel(img, x + i, y, color);
	}
}

void draw_matrix(t_matrix *matrix, void *mlx, void *win)
{
	for (int i = 0; i < MAX_MATRIX; i++)
	{
		for (int j = 0; j < TRAIL_SIZE; j++)
		{
			if (matrix[i].x > 200 && matrix[i].x < WIN_WIDTH - 200)
				continue ;
			int y = (int)matrix[i].y - (j * 12);

			if (y < 0)
				continue;

			char str[2];
			str[0] = matrix[i].trail[j];
			str[1] = '\0';

			int color;

			if (j == 0)
				color = 0x8899AA;
			else if (j < 3)
				color = 0x445566;
			else
				color = 0x223344;

			mlx_string_put(mlx, win, matrix[i].x, y, color, str);
		}
	}
}


void	draw_panel(t_img *img)
{
	int w = 400;
	int h = 400;
	int start_x = (img->width - w) / 2;
	int start_y = (img->height - h) / 2;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int px = start_x + x;
			int py = start_y + y;

			// fundo semi escuro
			put_pixel(img, px, py, 0x080812);

			// borda
			if (x == 0 || x == w - 1 || y == 0 || y == h - 1)
				put_pixel(img, px, py, 0x2A2A3A);

			// linha superior vermelha
			if (y == 0)
				put_pixel(img, px, py, 0x801E1E);
		}
	}
}

void render_title(t_data *game, double alpha)
{
	int	y;
	int	x;
	
	(void)alpha;
	y = (game->frame.height / 2);
	x = (game->frame.width / 2);
	draw_sky(game, 0x0A0A12, 0x0A0A1A);
	// render_leaves(game, alpha);

	int panel_w = 400;
	int panel_h = 400;

	int panel_x = (game->frame.width - panel_w) / 2;
	int panel_y = (game->frame.height - panel_h) / 2;

	draw_panel(&game->frame);

	// draw_rect(&game->frame, panel_x, panel_y, panel_w, panel_h, PANEL_COLOR);
	// draw_border(&game->frame, panel_x, panel_y, panel_w, panel_h, PANEL_BORDER);
	// draw_rect(&game->frame, panel_x + 2, panel_y + 2, panel_w - 4, panel_h - 4, 0x0f141f);

	int line_w = 370;
	int line_x = (game->frame.width - line_w) / 2;

	draw_line_fancy(&game->frame, line_x, panel_y + 135, line_w);
	draw_line_fancy(&game->frame, line_x, panel_y + 350, line_w);

	draw_sprite_to_frame(game, &game->logo, x - (game->logo.width / 2), y - 50, 0);
	
	// draw_button(game, &game->btn[0]);
	// draw_button(game, &game->btn[1]);

	draw_sprite_to_frame(game, &game->logo_42, 770, 570, 0);

	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	
	draw_matrix(game->matrix, game->mlx, game->win);
	
	mlx_set_font(game->mlx, game->win, "12x24");
	int text_width = 9 * 9; // 9 chars * ~9px
	int x2 = (800 / 2) - (text_width / 2);
	mlx_string_put(game->mlx, game->win, x2 - 10, panel_y + 180, 0xFFFFFF, "C U B 3 D");
	mlx_set_font(game->mlx, game->win, "fixed");

	
	mlx_string_put(game->mlx, game->win, panel_x + 25, panel_y + 40, 0xFF5555, "[ CONFIDENTIAL FILE ]");
	mlx_string_put(game->mlx, game->win, panel_x + 20, panel_y + 80, 0xAAAAAA, "Project: #######");
	mlx_string_put(game->mlx, game->win, panel_x + 20, panel_y + 100, 0xAAAAAA, "Status:");
	mlx_string_put(game->mlx, game->win, panel_x + 70, panel_y + 100, 0x00FF88, "ACTIVE");
	mlx_string_put(game->mlx, game->win, panel_x + 20, panel_y + 120, 0xAAAAAA, "Clearance:");
	mlx_string_put(game->mlx, game->win, panel_x + 90, panel_y + 120, 0xFF4444, "DENIED");
	
	mlx_string_put(game->mlx, game->win, 10, 590, 0xffffff, "By: Amyrodri and Cassunca");
}

void	update_leaves(t_data *game, double dt)
{
	int		i;
	t_leaf	*l;

	i = 0;
	while (i< MAX_LEAVES)
	{
		l = &game->leaves[i];
		l->prev_x = l->x;
		l->prev_y = l->y;
		l->time += dt;
		l->y += l->speed_y * dt;
		l->x += sin(l->time * l->frequency) * l->amplitude * dt;
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
		if (l->y > WIN_HEIGHT)
			init_leaf(l);
		i++;
	}
}

void update_matrix(t_matrix *matrix, float dt)
{
	for (int i = 0; i < MAX_MATRIX; i++)
	{
		matrix[i].y += matrix[i].speed * dt;

		// só atualiza quando andou 12 pixels (altura da letra)
		if ((int)(matrix[i].y / 12) != (int)(matrix[i].last_y / 12))
		{
			// shift do rastro
			for (int j = TRAIL_SIZE - 1; j > 0; j--)
				matrix[i].trail[j] = matrix[i].trail[j - 1];

			// nova letra entra aqui
			matrix[i].trail[0] = rand() % 94 + 33;
		}

		matrix[i].last_y = matrix[i].y;

		if (matrix[i].y > WIN_HEIGHT)
		{
			matrix[i].y = 0;
			matrix[i].x = rand() % WIN_WIDTH;
		}
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
		update_matrix(game->matrix, tick_rate);
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
