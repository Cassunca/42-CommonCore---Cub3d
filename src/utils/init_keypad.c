/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keypad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 23:48:51 by kamys             #+#    #+#             */
/*   Updated: 2026/04/13 00:40:09 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <string.h>

void	open_secret_door(t_data *game)
{
	int		target_x;
	int		target_y;
	t_door	*door;

	target_x = (int)(game->player.pos_x + game->player.dir_x);
	target_y = (int)(game->player.pos_y + game->player.dir_y);
	door = find_door(game, target_x, target_y);
	if (door)
		door->opening = 1;
}

void	key_clear(t_data *game, int value)
{
	while (game->password_len > 0)
	{
		game->password_len--;
		game->password_input[game->password_len] = '\0';
	}
	printf("clear value: %d\n", value);
}

void	key_add_digit(t_data *game, int value)
{
	if (game->password_len < 4)
	{
		game->password_input[game->password_len++] = '0' + value;
		game->password_input[game->password_len] = '\0';
	}
}

void	key_submit(t_data *game, int value)
{
	(void)value;
	game->password_input[game->password_len] = '\0';
	if (strcmp(game->password_input, "1234") == 0)
	{
		open_secret_door(game);
	}
	game->screen = GAME;
}

void	set_key_action(t_key *key)
{
	if (key->value == -1)
		key->action = key_clear;
	else if (key->value == -2)
		key->action = key_submit;
	else
		key->action = key_add_digit;
}

void	init_keypad(t_data *game, t_point pos, t_point size, t_point spacing)
{
	int			col;
	int			i;
	int			row;
	static int	values[4][3] = {
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9},
	{-1, 0, -2}
	};

	i = 0;
	while (i < MAX_KEYPAD)
	{
		row = i / 3;
		col = i % 3;
		game->keys[i] = (t_key){
			.x = pos.x + col * (size.x + spacing.x),
			.y = pos.y + row * (size.y + spacing.y),
			.w = size.x, .h = size.y,
			.is_hover = FALSE,
			.value = values[row][col],
		};
		set_key_action(&game->keys[i++]);
	}
}
