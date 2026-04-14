/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:35:55 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/13 19:37:41 by amyrodri         ###   ########.fr       */
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
		door->opening = TRUE;
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
	if (game->password_len < (int)ft_strlen(game->pw_door))
	{
		game->password_input[game->password_len++] = '0' + value;
		game->password_input[game->password_len] = '\0';
	}
}

void	key_submit(t_data *game, int value)
{
	(void)value;
	game->password_input[game->password_len] = '\0';
	if (strcmp(game->password_input, game->pw_door) == 0)
	{
		open_secret_door(game);
	}
	game->screen = GAME;
}
