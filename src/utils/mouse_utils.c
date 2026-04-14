/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:38:36 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/13 19:41:52 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_inside(int x, int y, t_key *key)
{
	return (
		x >= key->x
		&& x <= key->x + key->w
		&& y >= key->y
		&& y <= key->y + key->h
	);
}

void	update_keypad_hover(t_data *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < MAX_KEYPAD)
	{
		if (is_inside(x, y, &game->keys[i]))
			game->keys[i].is_hover = TRUE;
		else
			game->keys[i].is_hover = FALSE;
		i++;
	}
}

void	update_buttons_hover(t_data *game, int x, int y)
{
	t_button	*btn;
	int			i;

	i = 0;
	while (i < MAX_BTNS)
	{
		btn = &game->btn[i];
		btn->is_hover = (
				x >= btn->x && x <= btn->x + btn->w
				&& y >= btn->y && y <= btn->y + btn->h
				);
		if (btn->is_hover && !btn->glitching)
			btn->glitching = 1;
		i++;
	}
}

void	handle_button_click(t_data *game, t_button *btn,
	int mouse_x, int mouse_y)
{
	if (mouse_x >= btn->x && mouse_x <= btn->x + btn->w
		&& mouse_y >= btn->y && mouse_y <= btn->y + btn->h)
	{
		btn->on_click(game);
	}
}
