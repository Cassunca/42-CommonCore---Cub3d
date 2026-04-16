/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keypad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 23:48:51 by kamys             #+#    #+#             */
/*   Updated: 2026/04/13 19:37:19 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	key_submit(t_data *game, int value);
void	key_add_digit(t_data *game, int value);
void	key_clear(t_data *game, int value);

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
	game->password_input = malloc(ft_strlen(game->pw_door) + 1);
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
