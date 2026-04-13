/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 23:49:57 by kamys             #+#    #+#             */
/*   Updated: 2026/04/13 00:41:54 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	handle_button_click(t_data *game, t_button *btn,
	int mouse_x, int mouse_y)
{
	if (mouse_x >= btn->x && mouse_x <= btn->x + btn->w
		&& mouse_y >= btn->y && mouse_y <= btn->y + btn->h)
	{
		btn->on_click(game);
	}
}

static int	handle_click_area(int mx, int my, t_click *a)
{
	int		inside;
	char	*args[3];
	pid_t	pid;

	if (a->is_text)
		inside = (mx >= a->x && mx <= a->x + a->width
				&& my >= a->y - a->height && my <= a->y);
	else
		inside = (mx >= a->x && mx <= a->x + a->width
				&& my >= a->y && my <= a->y + a->height);
	if (inside)
	{
		pid = fork();
		if (pid == 0)
		{
			args[0] = "xdg-open";
			args[1] = a->url;
			args[2] = NULL;
			execv("/usr/bin/xdg-open", args);
			exit(1);
		}
		return (1);
	}
	return (0);
}

int	is_inside(int x, int y, t_key *key)
{
	return (
		x >= key->x
		&& x <= key->x + key->w
		&& y >= key->y
		&& y <= key->y + key->h
	);
}

static void	handle_keypad_click(t_data *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < MAX_KEYPAD)
	{
		if (is_inside(x, y, &game->keys[i]))
			game->keys[i].action(game, game->keys[i].value);
		i++;
	}
}

static void	handle_title_clicks(t_data *game, int x, int y)
{
	t_click	areas[3];
	int		i;

	areas[0] = (t_click){10, 590, 80, 15, "https://github.com/AmyRodri", 1};
	areas[1] = (t_click){100, 590, 90, 15, "https://github.com/Cassunca", 1};
	areas[2] = (t_click){770, 570, game->logo_42.width,
		game->logo_42.height, "https://www.42sp.org.br/", 0};
	i = 0;
	while (i < MAX_BTNS)
	{
		handle_button_click(game, &game->btn[i], x, y);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		handle_click_area(x, y, &areas[i]);
		i++;
	}
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_data	*game;

	game = (t_data *)param;
	if (button != 1)
		return (0);
	if (game->screen == PASSWORD_INPUT)
	{
		handle_keypad_click(game, x, y);
		return (0);
	}
	if (game->screen == TITLE)
		handle_title_clicks(game, x, y);
	return (0);
}

static void	update_keypad_hover(t_data *game, int x, int y)
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

static void	update_buttons_hover(t_data *game, int x, int y)
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

int	mouse_move(int x, int y, void *param)
{
	t_data	*game;

	game = (t_data *)param;
	if (game->screen == PASSWORD_INPUT)
		update_keypad_hover(game, x, y);
	update_buttons_hover(game, x, y);
	return (0);
}
