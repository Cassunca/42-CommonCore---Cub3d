/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:15:36 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/08 20:17:56 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	play_action(void *param)
{
	t_data *game = (t_data *)param;
	printf("play\n");
	game->screen = GAME;
}

void	quit_action(void *param)
{
	(void)param;
	close_window(param);
	exit(0);
}

t_button	create_button(int x, int y, int w, int h, char *text,
	void (*on_click)(void *))
{
	t_button	btn;

	btn.x = x;
	btn.y = y;
	btn.w = w;
	btn.h = h;
	btn.text = text;
	btn.on_click = on_click;
	btn.is_hover = FALSE;
	btn.glitching = 0;
	btn.glitch_timer = 0;
	ft_strlcpy(btn.render_text, text, sizeof(btn.render_text));
	return (btn);
}

