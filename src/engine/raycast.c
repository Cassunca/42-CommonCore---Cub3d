/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:01:24 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/15 12:02:17 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_info_door(t_data *data);

static void	set_dda_step(t_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.pos_x - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.pos_x)
			* data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.pos_y - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.pos_y)
			* data->ray.delta_dist_y;
	}
}

static void	calculate_line_height(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.wall_dist = data->ray.side_dist_x
			- data->ray.delta_dist_x;
	else
		data->ray.wall_dist = data->ray.side_dist_y
			- data->ray.delta_dist_y;
	data->ray.line_height = (int)(WIN_HEIGHT / data->ray.wall_dist);
	data->ray.draw_start = -data->ray.line_height / 2 + WIN_HEIGHT / 2;
	data->ray.draw_end = data->ray.line_height / 2 + WIN_HEIGHT / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	if (data->ray.draw_end >= WIN_HEIGHT)
		data->ray.draw_end = WIN_HEIGHT - 1;
}

static void	perform_dda(t_data *data)
{
	char	tile;

	data->ray.hit = 0;
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		tile = data->map.grid[data->ray.map_y][data->ray.map_x];
		if (tile == '1')
			data->ray.hit = 1;
		else if (handle_door_hit(data))
			data->ray.hit = 1;
	}
}

static void	init_ray_info(t_data *data, int x)
{
	data->ray.camera_x = 2 * x / (double)WIN_WIDTH - 1;
	data->ray.ray_dir_x = data->player.dir_x + data->player.plane_x
		* data->ray.camera_x;
	data->ray.ray_dir_y = data->player.dir_y + data->player.plane_y
		* data->ray.camera_x;
	if (data->ray.ray_dir_x == 0)
		data->ray.delta_dist_x = 1e30;
	else
		data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	if (data->ray.ray_dir_y == 0)
		data->ray.delta_dist_y = 1e30;
	else
		data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
}

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	sort_sprites(t_data *g)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < g->sprite_count - 1)
	{
		j = 0;
		while (j < g->sprite_count - i - 1)
		{
			if (g->sprites[j].dist < g->sprites[j + 1].dist)
			{
				tmp = g->sprites[j];
				g->sprites[j] = g->sprites[j + 1];
				g->sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	draw_sprites(t_data *g)
{
	int			i;
	t_sprite	*s;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			screen_x;
	int			sprite_h;
	int			sprite_w;
	int			draw_start_x;
	int			draw_end_x;
	int			draw_start_y;
	int			draw_end_y;
	int			stripe;
	int			y;

	i = 0;
	while (i < g->sprite_count)
	{
		s = &g->sprites[i];
		t_img *tex = &s->frames[s->current_frame];

		// 🔹 posição relativa ao player
		sprite_x = s->x - g->player.pos_x;
		sprite_y = s->y - g->player.pos_y;

		// 🔹 transformação de câmera
		inv_det = 1.0 / (g->player.plane_x * g->player.dir_y
				- g->player.dir_x * g->player.plane_y);

		transform_x = inv_det * (g->player.dir_y * sprite_x
				- g->player.dir_x * sprite_y);

		transform_y = inv_det * (-g->player.plane_y * sprite_x
				+ g->player.plane_x * sprite_y);

		// 🚫 atrás da câmera
		if (transform_y <= 0)
		{
			i++;
			continue ;
		}

		// 🔹 posição na tela
		screen_x = (int)((g->frame.width / 2)
				* (1 + transform_x / transform_y));

		// 🔹 tamanho (com proporção da textura)
		sprite_h = abs((int)(g->frame.height / transform_y));
		sprite_w = sprite_h * ((double)tex->width / tex->height);

		// 🔥 deixa menor que parede
		sprite_h *= 0.6;
		sprite_w *= 0.6;

		// 🔹 limites na tela
		draw_start_y = -sprite_h / 2 + g->frame.height / 2;
		draw_end_y = sprite_h / 2 + g->frame.height / 2;
		draw_start_x = -sprite_w / 2 + screen_x;
		draw_end_x = sprite_w / 2 + screen_x;

		// 🔒 clamp (evita lixo)
		if (draw_start_y < 0)
			draw_start_y = 0;
		if (draw_end_y >= g->frame.height)
			draw_end_y = g->frame.height - 1;
		if (draw_start_x < 0)
			draw_start_x = 0;
		if (draw_end_x >= g->frame.width)
			draw_end_x = g->frame.width - 1;

		// 🎨 desenhar sprite
		stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_w / 2 + screen_x))
					* tex->width / sprite_w) / 256;

			// 🧱 zbuffer (não atravessa parede)
			if (transform_y > 0 && stripe > 0
				&& stripe < g->frame.width
				&& transform_y < g->zbuffer[stripe])
			{
				y = draw_start_y;
				while (y < draw_end_y)
				{
					int d = y * 256 - g->frame.height * 128
						+ sprite_h * 128;

					int tex_y = ((d * tex->height)
							/ sprite_h) / 256;

					int color = get_pixel(tex, tex_x, tex_y);

					// transparência (preto invisível)
					if (color != 0x000000)
						put_pixel(&g->frame, stripe, y, color);

					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}

void	execute_raycast(t_data *data)
{
	int	x;

	x = 0;
	render_background(data);
	while (x < WIN_WIDTH)
	{
		init_ray_info(data, x);
		data->ray.map_x = (int)data->player.pos_x;
		data->ray.map_y = (int)data->player.pos_y;
		set_dda_step(data);
		perform_dda(data);
		calculate_line_height(data);
		draw_wall_column(data, x);
		data->zbuffer[x] = data->ray.wall_dist;
		x++;
	}
	// 🔥 NOVO: calcular distância
	int i = 0;
	while (i < data->sprite_count)
	{
		double dx = data->player.pos_x - data->sprites[i].x;
		double dy = data->player.pos_y - data->sprites[i].y;
		data->sprites[i].dist = dx * dx + dy * dy;
		i++;
	}

	// 🔥 NOVO: ordenar
	sort_sprites(data);

	draw_sprites(data);
	draw_minimap(data);
	draw_crosshair(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->frame.ptr, 0, 0);
	draw_info_door(data);
	str_num(data, (int)fps(), "fps: ", 70);
}
