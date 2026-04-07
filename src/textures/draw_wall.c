/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:43:54 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/07 16:53:34 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_tex_step(t_data *data, t_img *tex)
{
	double	step;

	step = (double)(tex->height / data->ray.line_height);
	return (step);
}

double	get_tex_pos(t_data *data, t_img *tex)
{
	double	step;
	double	pos;

	step = get_tex_step(data, tex);
	pos = (data->ray.draw_start - WIN_HEIGHT / 2.0
			+ data->ray.line_height / 2.0) * step;
	return (pos);
}

int	apply_shade(int color, int side)
{
	if (side == 1)
		return ((color >> 1) & 0x7F7F7F);
	return (color);
}

void	draw_wall_column(t_data *data, int x)
{
	t_img	*tex;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;

	tex = get_wall_tex(data);
	tex_x = get_tex_x(data, tex);
	step = get_tex_step(data, tex);
	tex_pos = get_tex_pos(data, tex);
	y = data->ray.draw_start;
	while (y <= data->ray.draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		my_mlx_pixel_put(&data->frame, x, y,
			apply_shade(get_tex_pixel(tex, tex_x, tex_y), data->ray.side));
		tex_pos += step;
		y++;
	}
}
