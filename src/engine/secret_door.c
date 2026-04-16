/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secret_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:58:35 by kamys             #+#    #+#             */
/*   Updated: 2026/04/16 16:24:18 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_key_text(t_data *g, t_key *key);
void	draw_key(t_data *g, t_key *key);
void	draw_dots(t_data *game, int input_x, int input_y);
void	draw_box(t_data *game, t_point pos);
void	draw_input_box(t_data *game, int x, int y);
int		draw_status_box(t_data *game, t_point pos, int input_x, int input_y);

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
		printf("Input Password:\n");
	}
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
	draw_keypad(game);
}
