/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:59:30 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/15 17:55:07 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (tv.tv_usec / 1000000.0));
}

void	my_usleep(double seconds)
{
	double	start;
	double	end;

	start = get_time();
	end = get_time();
	while (end - start < seconds)
		end = get_time();
}

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	init_sprites(t_data *g)
{
	t_sprite	*s;
	int			x;
	int			y;

	g->sprite_count = 0;
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(g->map.grid[y]))
		{
			if (g->map.grid[y][x] == 'T')
			{
				s = &g->sprites[g->sprite_count];
				*s = (t_sprite){
					.x = x + 0.5, .y = y + 0.5,
					.frames = g->sign_frames,
					.frame_count = MAX_THAWAN, .current_frame = 0,
					.last_update = get_time(), .delay = 0.12};
				g->sprite_count++;
			}
			x++;
		}
		y++;
	}
}
