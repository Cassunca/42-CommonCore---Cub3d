/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_keypad_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:48:07 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/13 19:57:17 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_key_label(t_key *key, char *buf)
{
	if (key->value >= 0 && key->value <= 9)
	{
		buf[0] = key->value + '0';
		buf[1] = '\0';
	}
	else if (key->value == -1)
		ft_strlcpy(buf, "C", 3);
	else if (key->value == -2)
		ft_strlcpy(buf, "OK", 3);
	else
		return (NULL);
	return (buf);
}

static int	get_text_color(t_key *key)
{
	if (key->is_hover)
		return (0xFFFFFF);
	if (key->value == -1)
		return (0xff6b6b);
	if (key->value == -2)
		return (0x00FF99);
	return (0x88e6ff);
}

void	draw_key_text(t_data *g, t_key *key)
{
	char	str[3];
	char	*label;
	int		x;
	int		y;

	label = get_key_label(key, str);
	if (!label)
		return ;
	x = key->x + (key->w - (ft_strlen(label) * 9)) / 2;
	y = key->y + key->h / 2 + 5;
	mlx_set_font(g->mlx, g->win, "9x15bold");
	mlx_string_put(g->mlx, g->win, x, y, get_text_color(key), label);
	mlx_set_font(g->mlx, g->win, "fixed");
}

static int	get_key_color(int value)
{
	if (value == -1)
		return (0xff6b6b);
	else if (value == -2)
		return (0x00ff64);
	return (0x99DDFF);
}

void	draw_key(t_data *g, t_key *key)
{
	t_shape	shape;
	int		color;

	shape = (t_shape){
		.x = key->x,
		.y = key->y,
		.w = key->w,
		.h = key->h,
		.radius = 10,
		.border_thickness = 2,
		.type = SHAPE_RECT,
	};
	color = get_key_color(key->value);
	shape.border_color = color;
	shape.fill_color = 0;
	if (key->is_hover)
		shape.fill_color = 0x030815;
	if (key->is_hover && key->value != -1 && key->value != -2)
		shape.border_color = 0x00FFFF;
	draw_shape(&g->frame, shape);
}
