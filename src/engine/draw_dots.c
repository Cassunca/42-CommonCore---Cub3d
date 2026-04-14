/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dots.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:52:16 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/13 19:57:30 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_code_dots(t_data *game, int start_x, int y)
{
	int	i;
	int	spacing;
	int	fill_color;

	i = 0;
	spacing = DOT_SPACING;
	while (i < (int)ft_strlen(game->pw_door))
	{
		fill_color = 0x000000;
		if (i < game->password_len)
			fill_color = 0x00FFFF;
		draw_shape(&game->frame,
			(t_shape){
			.x = start_x + (i * (DOT_SIZE + spacing)),
			.y = y,
			.w = DOT_SIZE,
			.h = DOT_SIZE,
			.radius = 0,
			.fill_color = fill_color,
			.border_color = 0x99DDFF,
			.border_thickness = 1,
			.type = SHAPE_CIRCLE
		});
		i++;
	}
}

void	draw_dots(t_data *game, int input_x, int input_y)
{
	int	dots_w;
	int	dots_x;
	int	dots_y;
	int	dots_count;

	dots_count = (int)ft_strlen(game->pw_door);
	dots_w = dots_count * DOT_SIZE + (dots_count - 1) * DOT_SPACING;
	dots_x = input_x + (INPUT_W - dots_w) / 2;
	dots_y = input_y + (INPUT_H - DOT_SIZE) / 2;
	draw_code_dots(game, dots_x, dots_y);
}
