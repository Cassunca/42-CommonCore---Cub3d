/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 23:49:57 by kamys             #+#    #+#             */
/*   Updated: 2026/04/09 00:00:11 by kamys            ###   ########.fr       */
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

int	mouse_hook(int button, int x, int y, void *param)
{
	t_data			*game;
	t_click			areas[3];
	int				i;

	game = (t_data *)param;
	if (game->screen != TITLE || button != 1)
		return (0);
	areas[0] = (t_click){10, 590, 80, 15, "https://github.com/AmyRodri", 1};
	areas[1] = (t_click){100, 590, 90, 15, "https://github.com/Cassunca", 1};
	areas[2] = (t_click){770, 570, game->logo_42.width, game->logo_42.height,
		"https://www.42sp.org.br/", 0};
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
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_data		*game;
	t_button	*btn;
	int			i;

	game = (t_data *)param;
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
	return (0);
}
