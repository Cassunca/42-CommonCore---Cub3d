/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:15:36 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/09 12:47:01 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	play_action(void *param)
{
	t_data	*game;

	game = (t_data *)param;
	printf("play\n");
	game->screen = GAME;
}

void	quit_action(void *param)
{
	(void)param;
	close_window(param);
	exit(0);
}

t_button	create_button(t_point pos, t_point size, char *text,
					void (*on_click)(void *))
{
	t_button	btn;

	btn.x = pos.x;
	btn.y = pos.y;
	btn.w = size.x;
	btn.h = size.y;
	btn.text = text;
	btn.on_click = on_click;
	btn.is_hover = FALSE;
	btn.glitching = 0;
	btn.glitch_timer = 0;
	ft_strlcpy(btn.render_text, text, sizeof(btn.render_text));
	return (btn);
}
