/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:10:25 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/15 18:11:37 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	get_dist_object(t_data *g)
{
	double	dx;
	double	dy;
	int		i;

	i = 0;
	while (i < g->sprite_count)
	{
		dx = g->player.pos_x - g->sprites[i].x;
		dy = g->player.pos_y - g->sprites[i].y;
		g->sprites[i].dist = dx * dx + dy * dy;
		i++;
	}
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
