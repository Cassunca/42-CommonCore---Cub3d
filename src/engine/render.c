/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:01:45 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/13 00:54:29 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				my_mlx_pixel_put(&data->frame, x, y, 0x87CEEB);
			else
				my_mlx_pixel_put(&data->frame, x, y, 0x8B4513);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->frame.ptr, 0, 0);
}

void	draw_crosshair(t_data *data)
{
	int	cx;
	int	cy;

	cx = WIN_WIDTH / 2;
	cy = WIN_HEIGHT / 2;
	put_pixel(&data->frame, cx, cy, 0xFFFFFF);
	put_pixel(&data->frame, cx - 5, cy, 0xFFFFFF);
	put_pixel(&data->frame, cx + 5, cy, 0xFFFFFF);
	put_pixel(&data->frame, cx, cy - 5, 0xFFFFFF);
	put_pixel(&data->frame, cx, cy + 5, 0xFFFFFF);
}
