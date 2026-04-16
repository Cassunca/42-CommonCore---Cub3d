/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:57:19 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/09 00:07:54 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	brighten(int color, float factor)
{
	int	r;
	int	g;
	int	b;

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

void	draw_pixel_safe(t_data *game, t_img *sprite, t_point frame_pt,
							t_point sprite_pt)
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
			put_pixel(&game->frame, frame_pt.x, frame_pt.y, color);
		}
	}
}

void	draw_sprite_to_frame(t_data *game, t_img *sprite, int x, int y)
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
				draw_pixel_safe(game, sprite, frame_pt, sprite_pt);
				sprite_pt.x++;
			}
		}
		sprite_pt.y++;
	}
}
