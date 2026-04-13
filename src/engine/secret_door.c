/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secret_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:58:35 by kamys             #+#    #+#             */
/*   Updated: 2026/04/13 01:28:50 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_secret_door(t_data *game, t_door *door)
{
	if (door->open != 0.0)
	{
		door->opening = -1;
		return ;
	}
	if (game->screen != PASSWORD_INPUT)
	{
		game->screen = PASSWORD_INPUT;
		game->password_len = 0;
		game->password_input[0] = '\0';
		printf("Digite a senha:\n");
	}
}

void	draw_code_dots(t_data *game, int start_x, int y)
{
	int	i;
	int	spacing;
	int	fill_color;

	i = 0;
	spacing = 30;
	while (i < 4)
	{
		fill_color = 0x000000;
		if (i < game->password_len)
			fill_color = 0x00FFFF;
		draw_shape(&game->frame,
			(t_shape){
			.x = start_x + (i * (12 + spacing)),
			.y = y,
			.w = 12,
			.h = 12,
			.radius = 0,
			.fill_color = fill_color,
			.border_color = 0x99DDFF,
			.border_thickness = 1,
			.type = SHAPE_CIRCLE
		});
		i++;
	}
}

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

void	draw_keypad(t_data *game)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		draw_key(game, &game->keys[i]);
		draw_key_text(game, &game->keys[i]);
		i++;
	}
}

void	draw_keys(t_data *game)
{
	int	i;

	i = 0;
	while (i < MAX_KEYPAD)
	{
		draw_key(game, &game->keys[i]);
		draw_key_text(game, &game->keys[i]);
		i++;
	}
}

void	draw_texts(t_data *game, t_point pos, t_point input, int rect_y)
{
	mlx_string_put(game->mlx, game->win,
		input.x + 10,
		input.y + 20,
		0x99DDFF,
		"INPUT CODE");
	mlx_set_font(game->mlx, game->win, "10x20");
	mlx_string_put(game->mlx, game->win,
		pos.x + (PANEL_W - (15 * 10)) / 2,
		pos.y + 40,
		0x00FFFF,
		"ACCESS REQUIRED");
	mlx_set_font(game->mlx, game->win, "9x15");
	mlx_string_put(game->mlx, game->win,
		pos.x + (PANEL_W - (14 * 9)) / 2,
		rect_y + 25,
		0x99DDFF,
		"STATUS: LOCKED");
	mlx_set_font(game->mlx, game->win, "fixed");
}

void	render_frame(t_data *game)
{
	mlx_mouse_show(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
}

int	draw_status_box(t_data *game, t_point pos, int input_x, int input_y)
{
	int	keypad_top;
	int	middle_y;
	int	rect_y;

	keypad_top = pos.y + 220;
	middle_y = (input_y + INPUT_H + keypad_top) / 2;
	rect_y = middle_y - (STATUS_H / 2);
	draw_shape(&game->frame, (t_shape){
		input_x, rect_y,
		INPUT_W, STATUS_H,
		5,
		0x0D1B22, 0x99DDFF, 2,
		SHAPE_RECT
	});
	return (rect_y);
}

void	draw_dots(t_data *game, int input_x, int input_y)
{
	int	dots_w;
	int	dots_x;
	int	dots_y;

	dots_w = DOT_COUNT * DOT_SIZE + (DOT_COUNT - 1) * DOT_SPACING;
	dots_x = input_x + (INPUT_W - dots_w) / 2;
	dots_y = input_y + (INPUT_H - DOT_SIZE) / 2;
	draw_code_dots(game, dots_x, dots_y);
}

void	draw_input_box(t_data *game, int x, int y)
{
	draw_shape(&game->frame, (t_shape){
		x, y,
		INPUT_W, INPUT_H,
		12,
		0x081218, 0x99DDFF, 2,
		SHAPE_RECT
	});
}

void	draw_box(t_data *game, t_point pos)
{
	draw_shape(&game->frame, (t_shape){
		pos.x, pos.y,
		PANEL_W, PANEL_H,
		20,
		0x060f20, 0x00FFFF, 2,
		SHAPE_RECT
	});
}

void	render_door_keypad(t_data *game)
{
	int		rect_y;
	int		input_x;
	int		input_y;
	t_point	pos;

	pos = (t_point){
		.x = (game->frame.width - PANEL_W) / 2,
		.y = (game->frame.height - PANEL_H) / 2
	};
	input_x = pos.x + (PANEL_W - INPUT_W) / 2;
	input_y = pos.y + 60;
	draw_box(game, pos);
	draw_input_box(game, input_x, input_y);
	draw_dots(game, input_x, input_y);
	rect_y = draw_status_box(game, pos, input_x, input_y);
	draw_keypad(game);
	render_frame(game);
	draw_texts(game, pos, (t_point){input_x, input_y}, rect_y);
	draw_keys(game);
}
